using CommunicationProtocol;
using engine.wrapper;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KaroManager
{
	public class KaroCommunicatedGameManager : KaroGameManager
	{
		private ICommunication _communication;
		private CommunicationProtocolConversionUtility _conversion;
		private int _turn = 0;
		private Random rand = new Random(1340);

		public KaroCommunicatedGameManager(ICommunication communication)
			: base()
		{
			CurrentPlayer = Players.Min;
			_conversion = new CommunicationProtocolConversionUtility(Game);
			_communication = communication;
			_communication.Connected += Communication_Connected;
			_communication.Disconnected += Communication_Disconnected;
			_communication.RequestFirstMove += Communication_RequestFirstMove;
			_communication.SentMoveInvalid += Communication_SentMoveInvalid;
			_communication.TurnReceived += Communication_TurnReceived;
			_communication.WinAccepted += Communication_WinAccepted;
			_communication.WinDetected += Communication_WinDetected;
			_communication.WinRejected += Communication_WinRejected;
		}

		void Communication_WinRejected()
		{
			Debug.WriteLine("Opponent did not accept win.");
		}

		void Communication_WinDetected(Turn t, Player p)
		{
			if (p == Player.Me)
			{
				Debug.WriteLine("Opponent thinks he won, going to check.");
				if(!HandleTheirMove(t)){
					return;
				}
				if (Game.HasWon(Players.Min))
				{
					Debug.WriteLine("Opponent did win, we lose.");
					_communication.SendWinAccepted();
				}
				else
				{
					Debug.WriteLine("Opponent thinks he won but didnt according to us.");
					_communication.SendWinDisputed();
				}
			}
			else if (p == Player.You)
			{
				Debug.WriteLine("Opponent thinks I won, going to check.");
				if (Game.HasWon(Players.Max))
				{
					Debug.WriteLine("We actually won without noticing?");
					_communication.SendWinAccepted();
				}
				else
				{
					Debug.WriteLine("We didnt win according to our calculations.");
					_communication.SendWinDisputed();
				}
			}
		}

		void Communication_WinAccepted()
		{
			Debug.WriteLine("We won!");
		}

		bool IsMoveLegal(MoveWrapper mv, Players player)
		{
			if (mv.GetMoveType() == engine.wrapper.MoveType.INSERT)
			{
				return FindLegalMoves(player).
					Any(m => m.GetToCell() == mv.GetToCell());
			}
			return FindLegalMoves(player).Any(m =>
				m.GetFromCell() == mv.GetFromCell() &&
				m.GetToCell() == mv.GetToCell() &&
				(!m.HasUsedCell() || m.GetUsedCell() == mv.GetUsedCell()));
		}

		bool HandleTheirMove(Turn t){
			Debug.WriteLine("Opponent took a turn");
			if (t == null)
			{
				Console.WriteLine("Turn is null, sending back");
				_communication.SendMoveInvalid(t);
				return false;
			}
			Debug.WriteLine("Received turn: " + _conversion.TurnToString(t) + " - " + (t.EmptyTile == null));
			MoveWrapper received = _conversion.ConvertTurnToMove(t);
			Debug.WriteLine("Converted turn to move: " + _conversion.MoveWrapperToString(received));

			// Get the move with the correct source tile from the last click.
			Console.WriteLine("Current player: " + CurrentPlayer);
			if (!IsMoveLegal(received, CurrentPlayer))
			{
				Console.WriteLine("Move is illegal, sending back");
				_communication.SendMoveInvalid(t);
				return false;
			}
			ExecuteMove(received);
			return true;
		}
		void Communication_TurnReceived(Turn t)
		{
			if (CurrentPlayer == Players.Max)
			{
				//Not their turn
				_communication.SendDisconnect(DisconnectReason.InvalidMove);
				return;
			}
			if(!HandleTheirMove(t)){
				return;
			}
			_turn++;

			//Handled their move, moving to ours now
			if (OnBoardUpdated != null)
				OnBoardUpdated();

			//System.Threading.Thread.Sleep(1000);
			CurrentPlayer = Players.Max;
			MoveWrapper bm = GetMove();
			Turn turn = _conversion.ConvertMoveToTurn(bm);
			ExecuteMove(bm);
			_turn++;

			if (Game.HasWon(Players.Max))
			{
				Debug.WriteLine("We won, sending message to opponent.");
				_communication.SendWinDetected(Player.Me, turn);
			}
			else
			{
				Debug.WriteLine("Move made, sending move to opponent.");
				_communication.SendTurn(turn);
			}
			Debug.WriteLine("Move sent to opponent: " + _conversion.MoveWrapperToString(bm));
			Debug.WriteLine("Converted move to turn: " + _conversion.TurnToString(turn));
			if (OnBoardUpdated != null)
				OnBoardUpdated();
			CurrentPlayer = Players.Min;
		}

		void Communication_SentMoveInvalid(Turn t)
		{
			Debug.WriteLine("Opponent says our move is wrong.");
		}

		void Communication_RequestFirstMove()
		{
			_turn++;
			Debug.WriteLine("We're first.");
			CurrentPlayer = Players.Max;
			MoveWrapper bm = GetMove();
			ExecuteMove(bm);
			_communication.SendTurn(_conversion.ConvertMoveToTurn(bm));
			Debug.WriteLine("Move sent to opponent: " + _conversion.MoveWrapperToString(bm));
			Debug.WriteLine("Converted move to turn: " + _conversion.TurnToString(_conversion.ConvertMoveToTurn(bm)));
			if (OnBoardUpdated != null)
				OnBoardUpdated();
			CurrentPlayer = Players.Min;
		}

		MoveWrapper GetMove() {
            MoveWrapper move = Game.GetBestMove();

            Console.WriteLine("Computer Player - Eval Count = {0}, Nodes Seen = {1}", Game.GetStaticEvalCallCount(), Game.GetNodesSeenCount());

			return move;
		}

		void Communication_Disconnected(DisconnectReason reason)
		{
			Debug.WriteLine("Opponent disconnected, reason: " + reason.ToString());
		}

		void Communication_Connected()
		{
			Debug.WriteLine("Connected to opponent, GLHF");
		}

		public override void Update(MouseClick tileLocation)
		{

		}
	}
}
