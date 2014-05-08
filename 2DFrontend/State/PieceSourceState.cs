using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
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
				m.GetFromCell() == new Vector2DWrapper(click.X, click.Y));

			foreach (MoveWrapper mw in legalMoves)
			{
				var from = mw.GetFromCell();
				var to = mw.GetToCell();
				var type = mw.GetMoveType();
			}

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
