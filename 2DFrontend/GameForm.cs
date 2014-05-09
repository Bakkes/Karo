using System;
using System.Net;
using System.Windows.Forms;
using CommunicationProtocol;
using KaroManager;

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


		private void serverToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ICommunication communication = new Server(43594);
			_manager = new KaroCommunicatedGameManager(communication);
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
				karoPanel.NewGame(_manager);
			} catch(Exception) {
				MessageBox.Show("IP incorrect");
			}
		}

		public void CommunicationFailed()
		{
			MessageBox.Show("Could not reach server");
		}
	}
}
