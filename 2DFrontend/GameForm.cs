using System;
using System.Windows.Forms;
using engine.wrapper;
using CommunicationProtocol;
using System.Net;

namespace _2DFrontend
{
	public partial class Karo : Form
	{
		/// <summary>
		/// The current gamestate.
		/// </summary>
		private KaroGameManager _manager;

		/// <summary>
		/// The last used communication module
		/// </summary>
		private ICommunication _communication;

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


		private void serverToolStripMenuItem_Click(object sender, EventArgs e)
		{
			_communication = new Server(43594);
			_manager = new KaroCommunicatedGameManager(_communication);
			karoPanel.NewGame(_manager);
		}

		private void clientToolStripMenuItem_Click(object sender, EventArgs e)
		{
			try {
				InputBox i = new InputBox();
				i.ShowDialog();
				string[] split = i.ResultText.Split(':');
				Client communication = new Client(IPAddress.Parse(split[0]), Int32.Parse(split[1]));
				_manager = new KaroCommunicatedGameManager(communication);
				communication.OnConnectionFailed += CommunicationFailed;
				communication.StartCommunicating();
				_communication = communication;
				karoPanel.NewGame(_manager);
			} catch(Exception) {
				MessageBox.Show("IP incorrect");
			}
		}

		public void CommunicationFailed()
		{
			MessageBox.Show("Could not reach server");
			CancelCommunication();
		}

		private void Karo_FormClosing(object sender, FormClosingEventArgs e)
		{
			CancelCommunication();
		}

		private void CancelCommunication()
		{
			if (_communication != null)
				_communication.CleanUp();
		}

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LoadBox loadBox = new LoadBox();
            DialogResult result = loadBox.ShowDialog(this);
            if (result == System.Windows.Forms.DialogResult.OK)
            {
                CancelCommunication();
                _manager = new KaroGameManager();
                _manager.Board.LoadFromString(loadBox.BoardString, loadBox.LeftTopX, loadBox.LeftTopY);
                karoPanel.NewGame(_manager);
            }
        }


	}
}
