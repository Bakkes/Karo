using CommunicationProtocol;
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
			throw new NotImplementedException();
		}

		void _communication_WinDetected(Turn t, Player p)
		{
			throw new NotImplementedException();
		}

		void _communication_WinAccepted()
		{
			throw new NotImplementedException();
		}

		void _communication_TurnReceived(Turn t)
		{
			throw new NotImplementedException();
		}

		void _communication_SentMoveInvalid(Turn t)
		{
			throw new NotImplementedException();
		}

		void communication_RequestFirstMove()
		{
			throw new NotImplementedException();
		}

		void _communication_Disconnected(DisconnectReason reason)
		{
			throw new NotImplementedException();
		}

		void _communication_Connected()
		{
			throw new NotImplementedException();
		}
	}
}
