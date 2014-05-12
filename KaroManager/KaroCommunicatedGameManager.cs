﻿using System;
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
			if (p == Player.You)
			{
				Debug.WriteLine("Opponent thinks he won, going to check.");
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
			else if (p == Player.Me)
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

		bool IsMoveLegal(MoveWrapper mv)
		{
			if (mv.GetMoveType() == engine.wrapper.MoveType.INSERT)
				return true;
			Vector2DWrapper from = mv.GetFromCell();
			Vector2DWrapper to = mv.GetToCell();
			Vector2DWrapper used = mv.GetUsedCell();
			Debug.WriteLine("Checking if legal: ");
			Debug.WriteLine(_conversion.MoveWrapperToString(mv));
			IEnumerable<MoveWrapper> legal = LegalMoves;
			return LegalMoves.Where(m =>
				m.GetFromCell() == mv.GetFromCell() && 
				m.GetToCell() == mv.GetToCell() &&
				(!m.HasUsedCell() || m.GetUsedCell() == mv.GetUsedCell())).Count() > 0;
		}

		void _communication_TurnReceived(Turn t)
		{
			

			Debug.WriteLine("Opponent took a turn");
			if (t == null)
			{
				Console.WriteLine("Turn is null, sending back");
				_communication.SendMoveInvalid(t);
				return;
			}
			Debug.WriteLine("Received turn: " + _conversion.TurnToString(t));
			MoveWrapper received = _conversion.ConvertTurnToMove(t);
			Debug.WriteLine("Converted turn to move: " + _conversion.MoveWrapperToString(received));

			// Get the move with the correct source tile from the last click.
			if(!IsMoveLegal(received)) {
				Console.WriteLine("Move is illegal, sending back");
				_communication.SendMoveInvalid(t);
				return;
			}
			ExecuteMove(received);
			_turn++;
			//Handled their move, moving on to ours now
			if (OnBoardUpdated != null)
				OnBoardUpdated();

			System.Threading.Thread.Sleep(1000);

			MoveWrapper bm = Game.GetBestMove();
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
			MoveWrapper bm = Game.GetBestMove();
			ExecuteMove(bm);
			_communication.SendTurn(_conversion.ConvertMoveToTurn(bm));
			Debug.WriteLine("Move sent to opponent: " + _conversion.MoveWrapperToString(bm));
			Debug.WriteLine("Converted move to turn: " + _conversion.TurnToString(_conversion.ConvertMoveToTurn(bm)));
			if (OnBoardUpdated != null)
				OnBoardUpdated();
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