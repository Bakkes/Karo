﻿using System.Collections.Generic;
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
		/// Width/height of the tiles in pixels.
		/// </summary>
		private const int TileSize = 50;

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
						TileWrapper tile = board.GetRelativeTileAt(new Vector2DWrapper(x, y));
						if ((tile.GetData() & (int)TileValue.HasTile) == (int)TileValue.HasTile)
						{
							Point paintPos = TileToPixel(x, y);
							g.FillRectangle(_tileBackColor, paintPos.X, paintPos.Y,
								TileSize, TileSize);
						}
					}
				}
			}
		}

		private void KaroPanel_MouseClick(object sender, MouseEventArgs e)
		{
			if (_manager != null)
			{
				_manager.Update(PixelToTile(e.Location.X, e.Location.Y));
				Invalidate();
			}
		}

		/// <summary>
		/// Translates pixel coordinates to tile coordinates.
		/// </summary>
		private Point PixelToTile(int x, int y)
		{
			// The +1 is because all tiles are offest by one tile to the bottom/right.
			// See comments in TileToPixel for further explanation.
			return new Point(x % (TileSize + Gap) + 1,
				y % (TileSize + Gap) + 1);
		}

		/// <summary>
		/// Translates tile coordinates to the topleft pixel coordinate of a tile.
		/// </summary>
		private Point TileToPixel(int x, int y)
		{
			// This makes sure there's always one empty row/colum at the top/left.
			// This is necessary to place your piece on the top/left nonexisting row.
			x++;
			y++;

			return new Point(x * (TileSize + Gap * 2) + Gap,
				y * (TileSize + Gap * 2) + Gap);
		}
	}
}
