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
			//CurrentState = null;
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
			//MoveWrapper received = new MoveWrapper();
		}

		void _communication_SentMoveInvalid(Turn t)
		{
			Console.WriteLine("Opponent says our move if wrong");
		}

		void communication_RequestFirstMove()
		{
			Console.WriteLine("We're first.");
		}

		void _communication_Disconnected(DisconnectReason reason)
		{
			Console.WriteLine("Opponent disconnected, reason: " + reason.ToString());
		}

		void _communication_Connected()
		{
			Console.WriteLine("Connected to opponent");
		}

		public override void Update(System.Drawing.Point tileLocation)
		{
			
		}

		private static MoveWrapper ConvertTurnToMove(Turn t)
		{
			engine.wrapper.MoveType mt;
			switch (t.MoveType)
			{
				case CommunicationProtocol.MoveType.Insert:
					mt = engine.wrapper.MoveType.Insert;
					break;
				case CommunicationProtocol.MoveType.Jump:
					mt = engine.wrapper.MoveType.Jump;
					break;
				case CommunicationProtocol.MoveType.Move:
					mt = engine.wrapper.MoveType.Move;
					break;
			}
			return new MoveWrapper(mt, ConvertIntToBoardPosition(t.FromTile),
				ConvertIntToBoardPosition(t.ToTile), ConvertIntToBoardPosition(t.EmptyTile));
		}
		private static Vector2DWrapper ConvertIntToBoardPosition(int number)
		{
			return Vector2DWrapper(number, number);
		}
	}
}
