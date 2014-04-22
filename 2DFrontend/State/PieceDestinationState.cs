﻿using System;
using System.Linq;
using System.Collections.Generic;
using System.Drawing;
using engine.wrapper;

namespace _2DFrontend.State
{
	/// <summary>
	/// In this state, the player will decide on which tile he wants to move
	/// his piece to. If clicked on a non valid tile, the game will go back to
	/// the PieceSourceState.
	/// </summary>
	class PieceDestinationState : IKaroState
	{
		private static PieceDestinationState _instance;

		public static IKaroState Instance
		{
			get
			{
				if (_instance == null)
				{
					_instance = new PieceDestinationState();
				}
				return _instance;
			}
		}

		/// <summary>
		/// Private constructor for singleton.
		/// </summary>
		private PieceDestinationState()
		{
		}

		public void Update(KaroGameManager manager, Point click)
		{
			IEnumerable<MoveWrapper> legalMoves = manager.LegalMoves;

			// Get the move with the correct source tile from the last click.
			IEnumerable<MoveWrapper> sourceLegalMoves = legalMoves.Where(m =>
				m.GetFromCell() == manager.CurrentMove.GetFromCell());

			// Get the move (if it exists) with the correct destination tile.
			MoveWrapper move = sourceLegalMoves.FirstOrDefault(m =>
				m.GetToCell() == new Vector2DWrapper(click.X, click.Y));

			if (move != null)
			{
				// Check if the destination tile exists or if a tile has to be moved.
				if (move.HasUsedCell())
				{
					manager.CurrentMove = move;
					manager.ChangeState(CellSourceState.Instance);
				}
			}
			else
			{
				// Clicked on invalid destination tile. Get rid of the current
				// move and go back to PieceSourceState.
				manager.CurrentMove = null;
				manager.ChangeState(PieceSourceState.Instance);
			}
		}
	}
}