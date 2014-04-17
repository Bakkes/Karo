using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
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
				m.GetFromTile() == manager.CurrentMove.GetFromTile());

			// Get the move (if it exists) with the correct destination tile.
			MoveWrapper move = sourceLegalMoves.FirstOrDefault(m =>
				m.GetToTile() == new Vector2DWrapper(click.X, click.Y));

			if (move != null)
			{
				Debug.WriteLine("Clicked on valid destination");
				// Check if the destination tile exists or if a tile has to be moved.
				if (move.HasUsedTile())
				{
					Debug.WriteLine("Empty tile must be moved to destination");
					manager.CurrentMove = move;
					manager.ChangeState(TileSourceState.Instance);
				}
			}
			else
			{
				// Clicked on invalid destination tile. Get rid of the current
				// move and go back to PieceSourceState.
				Debug.WriteLine("Can't move selected piece to tile.", click);
				manager.CurrentMove = null;
				manager.ChangeState(PieceSourceState.Instance);
			}
		}

		public void Enter(KaroGameManager manager)
		{
			Debug.WriteLine("Entering PieceDestinationState...");
		}

		public void Exit(KaroGameManager manager)
		{
			Debug.WriteLine("Exiting PieceDestinationState...");
		}
	}
}
