using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using engine.wrapper;

namespace _2DFrontend
{
	/// <summary>
	/// 2D representation of the Karo game.
	/// </summary>
	class KaroPanel : Panel
	{
		/// <summary>
		/// The current state of the game.
		/// If it is null, there is no game running at the moment.
		/// </summary>
		private KaroGameManager _manager;

		/// <summary>
		/// The backcolor of Karo tiles.
		/// </summary>
		private Brush _tileBackColor = Brushes.White;

		/// <summary>
		/// Color of the circle accent on pieces.
		/// </summary>
		private Pen _pieceAccentColor = Pens.White;

		/// <summary>
		/// Color of max's pieces.
		/// </summary>
		private Brush _pieceMaxColor = Brushes.Green;

		/// <summary>
		/// Color of min's pieces.
		/// </summary>
		private Brush _pieceMinColor = Brushes.Red;

		/// <summary>
		/// Width/height of the tiles in pixels.
		/// </summary>
		private const int CellSize = 50;

		/// <summary>
		/// Gap left and right of every tile.
		/// </summary>
		private const int Gap = 3;

		public KaroPanel()
			: base()
		{
			BackColor = Color.CornflowerBlue;
			DoubleBuffered = true;
			MouseClick += KaroPanel_MouseClick;
		}

		/// <summary>
		/// Start tracking a new game.
		/// </summary>
		/// <param name="karoGame">The new game this panel should show.</param>
		public void NewGame(KaroGameManager manager)
		{
			_manager = manager;
			Invalidate();
		}

		/// <summary>
		/// Draw the current state of the karo game.
		/// </summary>
		protected override void OnPaint(PaintEventArgs e)
		{
			Graphics g = e.Graphics;

			if (_manager != null)
			{
				BoardWrapper board = _manager.Board;
				const int maxPotentialSize = 20;
				for (int x = 0; x < maxPotentialSize; x++)
				{
					for (int y = 0; y < maxPotentialSize; y++)
					{
						CellWrapper tile = board.GetRelativeCellAt(new Vector2DWrapper(x, y));
						PaintTile(tile, g, x, y);
					}
				}
			}
		}

		private void PaintTile(CellWrapper tile, Graphics g, int x, int y)
		{
			int tileData = tile.GetData();
			if ((tileData & (int)CellValue.HasCell) == 0)
			{
				// No cel, return.
				return;
			}
			Point paintPos = CellToPixel(x, y);
			g.FillRectangle(_tileBackColor, paintPos.X, paintPos.Y,
				CellSize, CellSize);
			if ((tileData & (int)CellValue.IsEmpty) == 0)
			{
				if ((tileData & (int)CellValue.IsMax) != 0)
				{
					g.FillEllipse(_pieceMaxColor, paintPos.X, paintPos.Y, CellSize, CellSize);
				}
				else
				{
					g.FillEllipse(_pieceMinColor, paintPos.X, paintPos.Y, CellSize, CellSize);
				}
			}
		}

		private void KaroPanel_MouseClick(object sender, MouseEventArgs e)
		{
			if (_manager != null)
			{
				_manager.Update(PixelToCell(e.Location.X, e.Location.Y));
				Invalidate();
			}
		}

		/// <summary>
		/// Translates pixel coordinates to tile coordinates.
		/// </summary>
		private Point PixelToCell(int x, int y)
		{
			// The +1 is because all tiles are offest by one tile to the bottom/right.
			// See comments in CellToPixel for further explanation.
			return new Point(x / (CellSize + Gap) - 1,
				y / (CellSize + Gap) - 1);
		}

		/// <summary>
		/// Translates tile coordinates to the topleft pixel coordinate of a tile.
		/// </summary>
		private Point CellToPixel(int x, int y)
		{
			// This makes sure there's always one empty row/colum at the top/left.
			// This is necessary to place your piece on the top/left nonexisting row.
			x++;
			y++;

			return new Point(x * (CellSize + Gap * 2) + Gap,
				y * (CellSize + Gap * 2) + Gap);
		}
	}
}
