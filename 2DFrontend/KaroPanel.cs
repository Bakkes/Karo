using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Windows.Forms;
using engine.wrapper;
using KaroManager;
using KaroManager.State;

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
		private Brush _tileBackColor = new SolidBrush(Color.FromArgb(78, 78, 78));

		/// <summary>
		/// Color of the circle accent on pieces.
		/// </summary>
		private Pen _pieceAccentColor = new Pen(Color.FromArgb(34, 34, 34), 5);

		/// <summary>
		/// Color of max's pieces.
		/// </summary>
		private Brush _pieceMaxColor = new SolidBrush(Color.FromArgb(234, 78, 67));

		/// <summary>
		/// Color of min's pieces.
		/// </summary>
		private Brush _pieceMinColor = new SolidBrush(Color.FromArgb(67, 212, 78));

		private Brush _suggestionColor = new SolidBrush(Color.FromArgb(78, 150, 150));

		/// <summary>
		/// Width/height of the tiles in pixels.
		/// </summary>
		private const int CellSize = 50;

		private const int AccentSize = 30;

		private const int PieceSize = 40;

		/// <summary>
		/// Gap left and right of every tile.
		/// </summary>
		private const int Gap = 3;

		public KaroPanel()
			: base()
		{
			BackColor = Color.FromArgb(12, 12, 12);
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
			_manager.OnBoardUpdated += BoardChanged;
			Invalidate();
		}

		public void BoardChanged()
		{
			Invalidate();
		}

		/// <summary>
		/// Draw the current state of the karo game.
		/// </summary>
		protected override void OnPaint(PaintEventArgs e)
		{
			Graphics g = e.Graphics;
			g.SmoothingMode = SmoothingMode.AntiAlias;

			if (_manager != null)
			{
				PaintLegalMove(g);
				PaintCurrentPlayer(g);

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

		/// <summary>
		/// Paints the currentplayer in the topright of the panel.
		/// </summary>
		private void PaintCurrentPlayer(Graphics g)
		{
			int x = this.Width - CellSize;
			int y = CellSize - PieceSize;
			int offset = (CellSize - PieceSize) / 2;
			Brush playerBrush = _manager.CurrentPlayer == Players.Max ? _pieceMaxColor : _pieceMinColor;
			g.FillRectangle(_tileBackColor, x - offset, y - offset, CellSize, CellSize);
			g.FillEllipse(playerBrush, x, y, PieceSize, PieceSize);
		}

		/// <summary>
		/// Paints a tile that's 2 pixels wider/taller than CellSize at every
		/// tile that's currently clickable.
		/// </summary>
		private void PaintLegalMove(Graphics g)
		{
			MoveWrapper currentMove = _manager.CurrentMove;
			if (_manager.CurrentState is PlaceState)
			{
				// Highlight every empty tile.
				foreach (MoveWrapper move in _manager.LegalMoves)
				{
					Point paintPos = CellToPixel((int)move.GetToCell().X, (int)move.GetToCell().Y);
					g.FillRectangle(_suggestionColor, paintPos.X - 2, paintPos.Y - 2,
						CellSize + 4, CellSize + 4);
				}
			}
			else if (_manager.CurrentState is PieceSourceState)
			{
				// Highlight every movable piece of the current player.
				foreach (MoveWrapper move in _manager.LegalMoves)
				{
					Point paintPos = CellToPixel((int)move.GetFromCell().X, (int)move.GetFromCell().Y);
					g.FillRectangle(_suggestionColor, paintPos.X - 2, paintPos.Y - 2,
						CellSize + 4, CellSize + 4);
				}
			}
			else if (_manager.CurrentState is PieceDestinationState)
			{
				// Highlight every destination of the currently selected piece.
				foreach (MoveWrapper move in _manager.LegalMoves.Where(m => m.GetFromCell() == currentMove.GetFromCell()))
				{
					Point paintPos = CellToPixel((int)move.GetToCell().X, (int)move.GetToCell().Y);
					g.FillRectangle(_suggestionColor, paintPos.X - 2, paintPos.Y - 2,
						CellSize + 4, CellSize + 4);
				}
			}
			else if (_manager.CurrentState is CellSourceState)
			{
				// Highlight every empty tile that can be moved to the currently
				// empty spot on the board.
				foreach (MoveWrapper move in _manager.LegalMoves.Where(m => m.GetToCell() == currentMove.GetToCell()))
				{
					Point paintPos = CellToPixel((int)move.GetUsedCell().X, (int)move.GetUsedCell().Y);
					g.FillRectangle(_suggestionColor, paintPos.X - 2, paintPos.Y - 2,
						CellSize + 4, CellSize + 4);
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
				Brush brush;
				if ((tileData & (int)CellValue.IsMax) != 0)
				{
					brush = _pieceMaxColor;
				}
				else
				{
					brush = _pieceMinColor;
				}
				g.FillEllipse(
					brush,
					paintPos.X + (CellSize - PieceSize) / 2,
					paintPos.Y + (CellSize - PieceSize) / 2,
					PieceSize, PieceSize
				);
				if ((tileData & (int)CellValue.IsFlipped) != 0)
				{
					g.DrawEllipse(
						_pieceAccentColor,
						paintPos.X + (CellSize - AccentSize) / 2,
						paintPos.Y + (CellSize - AccentSize) / 2,
						AccentSize, AccentSize
					);
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
