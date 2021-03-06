﻿using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using engine.wrapper;

namespace KaroManager.State
{
	/// <summary>
	/// In this state, the current player must pick one of his pieces. When
	/// a valid piece is chosen, the game will go to the PieceDestinationState
	/// so the player can decide where he wants to move his piece.
	/// </summary>
	public class PieceSourceState : IKaroState
	{
		private static PieceSourceState _instance;

		public static IKaroState Instance
		{
			get
			{
				if (_instance == null)
				{
					_instance = new PieceSourceState();
				}
				return _instance;
			}
		}

		/// <summary>
		/// Private constructor for singleton.
		/// </summary>
		private PieceSourceState()
		{
		}

		public void Update(KaroGameManager manager, MouseClick click)
		{
			IEnumerable<MoveWrapper> legalMoves = manager.FindLegalMoves(manager.CurrentPlayer);

			// See if there is any move with the same source as the clicked tile.
			MoveWrapper move = legalMoves.FirstOrDefault(m =>
				m.GetFromCell() == new Vector2DWrapper(click.Position.X, click.Position.Y));

			// Valid source piece clicked, save the move.
			if (move != null)
			{
				Debug.WriteLine("Valid source piece selected");
				manager.CurrentMove = move;
				manager.ChangeState(PieceDestinationState.Instance);
			}
			else
			{
				Debug.WriteLine("Clicked tile does not have a moveable piece");
			}
		}

		public void Enter(KaroGameManager manager)
		{
			Debug.WriteLine("Entering PieceSourceState...");
		}

		public void Exit(KaroGameManager manager)
		{
			Debug.WriteLine("Exiting PieceSourceState...");
		}
	}
}
