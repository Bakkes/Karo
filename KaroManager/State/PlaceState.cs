﻿using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using engine.wrapper;

namespace KaroManager.State
{
	/// <summary>
	/// In this state, a human player can place a piece on an empty tile.
	/// </summary>
	public class PlaceState : IKaroState
	{
		/// <summary>
		/// The amount of pieces that have to be on the board in order for the
		/// game to advance to the next state.
		/// </summary>
		private const int MaxPieceCount = 6 * 2;
		private static PlaceState _instance;

		public static IKaroState Instance
		{
			get
			{
				if (_instance == null)
				{
					_instance = new PlaceState();
				}
				return _instance;
			}
		}

		/// <summary>
		/// Private constructor for singleton.
		/// </summary>
		private PlaceState()
		{
		}

		public void Update(KaroGameManager manager, MouseClick click)
		{
			IEnumerable<MoveWrapper> legalMoves = manager.FindLegalMoves(manager.CurrentPlayer);
			MoveWrapper move = legalMoves.FirstOrDefault(m =>
				m.GetToCell() == new Vector2DWrapper(click.Position.X, click.Position.Y));

			// We have a valid move.
			if (move != null)
			{

				Debug.WriteLine(move.GetToCell());
				CommunicationProtocolConversionUtility util = new CommunicationProtocolConversionUtility(manager.Game);
				Debug.WriteLine(util.TurnToString(util.ConvertMoveToTurn(move)));

				manager.ExecuteMove(move);
				Debug.WriteLine("Placed a new piece.");

			}
			else
			{
				manager.SendMoveIsNotValid();
				Debug.WriteLine("Can't place a new piece");
			}

			// Change state to Piece source state if all 6 pieces are on the board.
			if (manager.Board.GetOccupiedCells().Count == MaxPieceCount)
			{
				if (!(manager.CurrentState is ComputerState) && !(manager.CurrentState is WaitForUndoState))
				{
					Debug.WriteLine("All {0} pieces are placed at the board.", MaxPieceCount);
					manager.ChangeState(PieceSourceState.Instance);
				}
			}
		}

		public void Enter(KaroGameManager manager)
		{
			Debug.WriteLine("Entering PlaceState...");
		}

		public void Exit(KaroGameManager manager)
		{
			Debug.WriteLine("Exiting PlaceState...");
		}
	}
}
