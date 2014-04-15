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

		public KaroPanel()
			: base()
		{
			BackColor = Color.CornflowerBlue;
			DoubleBuffered = true;
		}

		/// <summary>
		/// Start tracking a new game.
		/// </summary>
		/// <param name="karoGame">The new game this panel should show.</param>
		public void NewGame(KaroGame karoGame)
		{
			_karoGame = karoGame;
		}
	}
}
