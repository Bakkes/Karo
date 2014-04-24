using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using engine.wrapper;

namespace _2DFrontend.State
{
	/// <summary>
	/// In this state, a human player can place a piece on an empty tile.
	/// </summary>
	class PlaceState : IKaroState
	{
		/// <summary>
		/// The amount of pieces that have to be on the board in order for the
		/// game to advance to the next state.
		/// </summary>
		private const int MaxPieceCount = 6;
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

		public void Update(KaroGameManager manager, Point click)
		{
			IEnumerable<MoveWrapper> legalMoves = manager.LegalMoves;
			MoveWrapper move = legalMoves.FirstOrDefault(m =>
				m.GetToCell() == new Vector2DWrapper(click.X, click.Y));

			// We have a valid move.
			if (move != null)
			{
				manager.ExecuteMove(move);
			}
			else
			{
				Debug.WriteLine("Can't place a new piece at the clicked tile.");
			}

			// Change state to Piece source state if all 6 pieces are on the board.
			if (manager.Board.GetOccupiedCells().Count == 6)
			{
				Debug.WriteLine("All {0} pieces are placed at the board.", MaxPieceCount);
				manager.ChangeState(PieceSourceState.Instance);
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
