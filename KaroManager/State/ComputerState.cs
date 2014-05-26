using System.Diagnostics;
using System.Drawing;

namespace KaroManager.State
{
	/// <summary>
	/// In this state, the computer will generate and place a move.
	/// </summary>
	public class ComputerState : IKaroState
	{
		private static ComputerState _instance;

		public static IKaroState Instance
		{
			get
			{
				if (_instance == null)
				{
					_instance = new ComputerState();
				}
				return _instance;
			}
		}

		/// <summary>
		/// Private constructor for singleton.
		/// </summary>
		private ComputerState()
		{
		}

		/// <summary>
		/// ComputerState doesn't listen to clickevents. The entry method will
		/// do everything AI related.
		/// </summary>
		public void Update(KaroGameManager manager, Point click)
		{
		}

		public void Enter(KaroGameManager manager)
		{
			Debug.WriteLine("Entering ComputerState...");
			manager.Game.ExecuteMove(
				manager.Game.GetBestMove(),
				manager.CurrentPlayer
			);
			manager.SwapCurrentPlayer();
			// Computer move executed

			if (manager.Board.GetOccupiedCells().Count < 12)
			{
				// Go back to the player's place state.
				manager.ChangeState(PlaceState.Instance);
			}
			else
			{
				// Go back to the player's piece source state.
				manager.ChangeState(PieceSourceState.Instance);
			}
		}

		public void Exit(KaroGameManager manager)
		{
			Debug.WriteLine("Exiting ComputerState...");
		}
	}
}
