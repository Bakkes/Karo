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
				m.GetFromCell() == manager.CurrentMove.GetFromCell());

			// Get the move (if it exists) with the correct destination tile.
			MoveWrapper move = sourceLegalMoves.FirstOrDefault(m =>
				m.GetToCell() == new Vector2DWrapper(click.X, click.Y));

			if (move != null)
			{
				var usedTile = move.HasUsedCell();
				Debug.WriteLine("Clicked on valid destination");
				// Check if the destination tile exists or if a tile has to be moved.
				if (move.HasUsedCell())
				{
					Debug.WriteLine("Empty tile must be moved to destination");
					manager.CurrentMove = move;
					manager.ChangeState(CellSourceState.Instance);
				}
				// Valid move, execute it.
				else
				{
					Debug.WriteLine("Moving tile at {0} to {1}",
						move.GetFromCell(), move.GetToCell());
					manager.ExecuteMove(move);

					//Debug.WriteLine(move.GetToCell());
					CommunicationProtocolConversionUtility util = new CommunicationProtocolConversionUtility(manager.Game);
					Debug.WriteLine(util.TurnToString(util.ConvertMoveToTurn(move)));

					manager.ChangeState(PieceSourceState.Instance);
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
