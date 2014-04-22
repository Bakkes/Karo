using CommunicationProtocol;
using engine.wrapper;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2DFrontend
{
	class KaroCommunicatedGameManager : KaroGameManager
	{
		private ICommunication _communication;
		public KaroCommunicatedGameManager(ICommunication communication)
			: base()
		{
			CurrentPlayer = Players.Min;
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
			Console.WriteLine("Opponent did not accept win.");
		}

		void _communication_WinDetected(Turn t, Player p)
		{
			Console.WriteLine("Opponent thinks he won, going to check.");
		}

		void _communication_WinAccepted()
		{
			Console.WriteLine("We won!");
		}

		void _communication_TurnReceived(Turn t)
		{
			Console.WriteLine("Opponent took a turn");
			MoveWrapper received = ConvertTurnToMove(t);

			// Get the move with the correct source tile from the last click.
			IEnumerable<MoveWrapper> sourceLegalMoves = LegalMoves.Where(m =>
				m.GetFromTile() == received.GetFromTile());

			// Get the move (if it exists) with the correct destination tile.
			IEnumerable<MoveWrapper> move = sourceLegalMoves.Where(m =>
				m.GetToTile() == received.GetToTile());

			MoveWrapper mv = move.FirstOrDefault(m => m.GetUsedTile() == received.GetUsedTile());
			if (mv == null)
			{
				_communication.SendMoveInvalid(t);
				return;
			}
			ExecuteMove(mv);
			//Handled their move, moving on to ours now

			MoveWrapper bm = Game.GetBestMove();
			ExecuteMove(bm);
		}

		void _communication_SentMoveInvalid(Turn t)
		{
			Console.WriteLine("Opponent says our move is wrong.");
			
		}

		void communication_RequestFirstMove()
		{
			Console.WriteLine("We're first.");
			CurrentPlayer = Players.Max;
			MoveWrapper bm = Game.GetBestMove();
			ExecuteMove(bm);
			_communication.SendTurn(ConvertMoveToTurn(bm));
		}

		void _communication_Disconnected(DisconnectReason reason)
		{
			Console.WriteLine("Opponent disconnected, reason: " + reason.ToString());

		}

		void _communication_Connected()
		{
			Console.WriteLine("Connected to opponent, GLHF");
		}

		public override void Update(System.Drawing.Point tileLocation)
		{
			
		}

		private static MoveWrapper ConvertTurnToMove(Turn t)
		{
			engine.wrapper.MoveType mt = engine.wrapper.MoveType.INSERT;
			switch (t.MoveType)
			{
				case CommunicationProtocol.MoveType.Insert:
					mt = engine.wrapper.MoveType.INSERT;
					break;
				case CommunicationProtocol.MoveType.Jump:
					mt = engine.wrapper.MoveType.JUMP;
					break;
				case CommunicationProtocol.MoveType.Move:
					mt = engine.wrapper.MoveType.MOVE;
					break;
			}
			return new MoveWrapper(mt, ConvertIntToBoardPosition(t.FromTile),
				ConvertIntToBoardPosition(t.ToTile), ConvertIntToBoardPosition(t.EmptyTile));
		}

		private static Turn ConvertMoveToTurn(MoveWrapper mw)
		{
			CommunicationProtocol.MoveType mt = CommunicationProtocol.MoveType.Insert;
			switch (mw.GetMoveType())
			{
				case engine.wrapper.MoveType.INSERT:
					mt = CommunicationProtocol.MoveType.Insert;
					break;
				case engine.wrapper.MoveType.JUMP:
					mt = CommunicationProtocol.MoveType.Jump;
					break;
				case engine.wrapper.MoveType.MOVE:
					mt = CommunicationProtocol.MoveType.Move;
					break;
			}
			Turn t = new Turn();
			t.MoveType = mt;
			t.EmptyTile = IntToVector2D(mw.GetUsedTile());
			t.FromTile = IntToVector2D(mw.GetFromTile());
			t.ToTile = IntToVector2D(mw.GetToTile());
			return t;
		}

		private static Vector2DWrapper ConvertIntToBoardPosition(int? number)
		{
			return new Vector2DWrapper(0.0, 0.0);
		}

		private static int IntToVector2D(Vector2DWrapper vector2D)
		{
			return (int)vector2D.X;
		}
	}
}
