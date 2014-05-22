using System;
using System.Net;
using System.Windows.Forms;
using CommunicationProtocol;
using engine.wrapper;
using KaroManager;
using System.Collections.Generic;

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
			_manager = new KaroComputerManager();
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
                _manager.CurrentPlayer = loadBox.CurrentPlayer;
                karoPanel.NewGame(_manager);
            }
        }

        private void showBoardStringToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (_manager == null)
                return;

            string boardString = _manager.Board.ToString();

            // Format string to be entered in C++ Unit test project
            boardString = '"' + boardString.Replace("\n", "\\n\"\r\n\"");
            boardString = boardString.Substring(0, boardString.Length - 1);

            Vector2DWrapper topLeft = _manager.Board.GetRelativeCellAt(new Vector2DWrapper(0, 0)).GetAbsolutePosition();

            LoadBox loadBox = new LoadBox(false);
            loadBox.BoardString = boardString;
            loadBox.LeftTopX = (int)topLeft.X;
            loadBox.LeftTopY = (int)topLeft.Y;
            loadBox.CurrentPlayer = _manager.CurrentPlayer;

            loadBox.ShowDialog();
        }

        private void zoomToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new RenderOptionsForm(karoPanel).Show();
        }

		private void copyMoveLogToolStripMenuItem_Click(object sender, EventArgs e)
		{
			//(STEP, Vector2D(1,1), Vector2D(0,1))
			string text = "";
			List<KeyValuePair<MoveWrapper, Players>> moves = _manager.MoveLog;
			foreach(KeyValuePair<MoveWrapper, Players> moveKV in moves) {
				MoveWrapper move = moveKV.Key;
				text += "board->ExecuteMove(Move(" + move.GetMoveType() + 
				", Vector2D(" + move.GetFromCell().X + ", " + move.GetFromCell().Y + "), " + 
				"Vector2D(" + move.GetToCell().X+", " + move.GetToCell().Y + ")), " + 
				(move.HasUsedCell() ? "Vector2D(" + move.GetUsedCell().X + ", " + move.GetUsedCell().Y + "), " : "") +
				moveKV.Value.ToString() + ");\n";
			}
			Clipboard.SetText(text);
		}

	}
}
