using System.Windows.Forms;
using engine.wrapper;

namespace _2DFrontend
{
	public partial class Karo : Form
	{
		/// <summary>
		/// The current gamestate.
		/// </summary>
		private KaroGame _karoGame;

		public Karo()
		{
			InitializeComponent();
		}
	}
}
