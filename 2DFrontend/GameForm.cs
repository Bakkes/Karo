using System;
using System.Windows.Forms;
using engine.wrapper;

namespace _2DFrontend
{
	public partial class Karo : Form
	{
		/// <summary>
		/// The current gamestate.
		/// </summary>
		private KaroGameManager _manager;

		public Karo()
		{
			InitializeComponent();
		}

		private void newToolStripMenuItem_Click(object sender, EventArgs e)
		{
			_manager = new KaroGameManager();
			karoPanel.NewGame(_manager);
		}

		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Close();
		}

		private void computerVSComputerToolStripMenuItem_Click(object sender, EventArgs e)
		{
			_manager = new KaroGameManager();
			karoPanel.NewGame(_manager);
		}
	}
}
