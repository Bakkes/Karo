using System.Diagnostics;
using System.Drawing;
using System.Threading;
using engine.wrapper;

namespace KaroManager.State
{
	/// <summary>
	/// In this state, the computer will generate and place a move.
	/// </summary>
	public class ComputerState : IKaroState
	{
		private static ComputerState _instance;
		private KaroGameManager _manager;
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

			Thread ExecuteThread = new Thread(ExecuteMoveThread);
			_manager = manager;
			ExecuteThread.Start();
		}

		public void Exit(KaroGameManager manager)
		{
			Debug.WriteLine("Exiting ComputerState...");
		}

		public void ExecuteMoveThread()
		{
			MoveWrapper move = _manager.Game.GetBestMove();
			Vector2DWrapper from = move.GetFromCell();
			Vector2DWrapper to = move.GetToCell();
			Vector2DWrapper used = move.HasUsedCell() ? move.GetUsedCell() : null;
			_manager.Game.ExecuteMove(
					move,
					_manager.CurrentPlayer
				);
			_manager.SwapCurrentPlayer();
			if (_manager.OnBoardUpdated != null)
			{
				_manager.OnBoardUpdated();
			}
			// Computer move executed

			if (_manager.Board.GetOccupiedCells().Count < 12)
			{
				// Go back to the player's place state.
				_manager.ChangeState(PlaceState.Instance);
			}
			else
			{
				// Go back to the player's piece source state.
				_manager.ChangeState(PieceSourceState.Instance);
			}

		}

	}

}
