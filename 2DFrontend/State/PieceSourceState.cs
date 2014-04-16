using System;
using System.Linq;
using System.Collections.Generic;
using System.Drawing;
using engine.wrapper;

namespace _2DFrontend.State
{
	/// <summary>
	/// In this state, the current player must pick one of his pieces. When
	/// a valid piece is chosen, the game will go to the PieceDestinationState
	/// so the player can decide where he wants to move his piece.
	/// </summary>
	class PieceSourceState : IKaroState
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

		public void Update(KaroGameManager manager, Point click)
		{
			IEnumerable<MoveWrapper> legalMoves = manager.LegalMoves;

			// See if there is any move with the same source as the clicked tile.
			MoveWrapper move = legalMoves.FirstOrDefault(m =>
				m.GetFromTile() == new Vector2DWrapper(click.X, click.Y));

			// Valid source piece clicked, save the move.
			if (move != null)
			{
				manager.CurrentMove = move;
			}
		}
	}
}
