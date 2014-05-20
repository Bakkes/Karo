using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using CommunicationProtocol;
using engine.wrapper;

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
			_communication.Connected += _communication_Connected;
			_communication.Disconnected += _communication_Disconnected;
			_communication.RequestFirstMove += communication_RequestFirstMove;
			_communication.SentMoveInvalid += _communication_SentMoveInvalid;
			_communication.TurnReceived += _communication_TurnReceived;
			_communication.WinAccepted += _communication_WinAccepted;
			_communication.WinDetected += _communication_WinDetected;
			_communication.WinRejected += _communication_WinRejected;
		}

		void _communication_WinRejected()
		{
			Debug.WriteLine("Opponent did not accept win.");
		}

		void _communication_WinDetected(Turn t, Player p)
		{
			// openent says he won (the message contains player.me)
			if (p == Player.Me)
			{
				Debug.WriteLine("Opponent thinks he won, going to check.");
				// c if execute their move
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

		void _communication_WinAccepted()
		{
			Debug.WriteLine("We won!");
		}

		bool IsMoveLegal(MoveWrapper mv, Players player)
		{
			if (mv.GetMoveType() == engine.wrapper.MoveType.INSERT)
				return true;
			Vector2DWrapper from = mv.GetFromCell();
			Vector2DWrapper to = mv.GetToCell();
			Vector2DWrapper used = mv.GetUsedCell();
			Debug.WriteLine("Checking if legal: ");
			Debug.WriteLine(_conversion.MoveWrapperToString(mv));
			IEnumerable<MoveWrapper> legal = Board.GetLegalMoves(player);
			;
			foreach (MoveWrapper mw in legal)
			{
				Vector2DWrapper from2 = mw.GetFromCell();
				Vector2DWrapper to2 = mw.GetToCell();
				Vector2DWrapper used2 = mw.GetUsedCell();
				bool hasUsed = mw.HasUsedCell();
				int a = 1;
			}
			return legal.Where(m =>
				m.GetFromCell() == mv.GetFromCell() &&
				m.GetToCell() == mv.GetToCell() &&
				(!m.HasUsedCell() || m.GetUsedCell() == mv.GetUsedCell())).Count() > 0;
		}

		private bool HandleTheirMove(Turn t){
			/*if (CurrentPlayer == Players.Max)
			{
				//Not their turn
				_communication.SendDisconnect(DisconnectReason.InvalidMove);
				return;
			}*/
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
			if (!IsMoveLegal(received, Players.Min))
			{
				Console.WriteLine("Move is illegal, sending back");
				_communication.SendMoveInvalid(t);
				return false;
			}
			ExecuteMove(received);
			return true;
		}
		void _communication_TurnReceived(Turn t)
		{
			if(!HandleTheirMove(t)){
				return;
			}
			_turn++;

			//Handled their move, moving on to ours now
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
			CurrentPlayer = Players.Min;
		}

		void _communication_SentMoveInvalid(Turn t)
		{
			Debug.WriteLine("Opponent says our move is wrong.");
		}

		void communication_RequestFirstMove()
		{
			_turn++;
			Debug.WriteLine("We're first.");
			CurrentPlayer = Players.Max;
			MoveWrapper bm = GetMove();
			ExecuteMove(bm);
			_communication.SendTurn(_conversion.ConvertMoveToTurn(bm));
			Debug.WriteLine("Move sent to opponent: " + _conversion.MoveWrapperToString(bm));
			Debug.WriteLine("Converted move to turn: " + _conversion.TurnToString(_conversion.ConvertMoveToTurn(bm)));
			CurrentPlayer = Players.Min;
		}
		MoveWrapper GetMove()
		{
			return LegalMoves.OrderBy(x => Guid.NewGuid()).Last(); //Game.GetBestMove();// LegalMoves.First(); // LegalMoves.OrderBy(x => Guid.NewGuid()).Last();
		}

		void _communication_Disconnected(DisconnectReason reason)
		{
			Debug.WriteLine("Opponent disconnected, reason: " + reason.ToString());
		}

		void _communication_Connected()
		{
			Debug.WriteLine("Connected to opponent, GLHF");
		}

		public override void Update(System.Drawing.Point tileLocation)
		{

		}
	}
}
