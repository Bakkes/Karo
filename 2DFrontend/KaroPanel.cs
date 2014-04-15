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
		private KaroGame _karoGame;

		/// <summary>
		/// The backcolor of Karo tiles.
		/// </summary>
		private Brush _tileBackColor = Brushes.White;

		/// <summary>
		/// Width/height of the tiles in pixels.
		/// </summary>
		private const int TileSize = 50;

		/// <summary>
		/// Gap between tiles in pixels.
		/// </summary>
		private const int Gap = 5;

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
		public void NewGame(KaroGame karoGame)
		{
			_karoGame = karoGame;
		}

		/// <summary>
		/// Draw the current state of the karo game.
		/// </summary>
		protected override void OnPaint(PaintEventArgs e)
		{
			Graphics g = e.Graphics;
			foreach (Point p in points)
			{
				int x = p.X * (TileSize + Gap) + Gap;
				int y = p.Y * (TileSize + Gap) + Gap;
				g.FillRectangle(_tileBackColor, x, y, TileSize, TileSize);
			}
		}

		List<Point> points = new List<Point>();

		private void KaroPanel_MouseClick(object sender, MouseEventArgs e)
		{
			if (false)
			{
				// Clicked on empty space, stop.
				return;
			}
			int x = (e.Location.X - Gap / 2) / (TileSize + Gap);
			int y = (e.Location.Y - Gap / 2) / (TileSize + Gap);
			points.Add(new Point(x, y));
			Invalidate();
		}
	}
}
