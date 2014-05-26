using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using engine.wrapper;
using KaroManager.State;

namespace KaroManager
{

	public delegate void BoardUpdated();
	public delegate void MoveExecuted(MoveWrapper move);

	/// <summary>
	/// Statemachine that keeps track of the game's states.
	/// </summary>
	public class KaroGameManager
	{
		/// <summary>
		/// Current state of the game.
		/// </summary>
		public IKaroState CurrentState { get; private set; }

		/// <summary>
		/// The player whose turn it is.
		/// </summary>
		public Players CurrentPlayer { get; set; }

		public BoardUpdated OnBoardUpdated;
		public MoveExecuted OnMoveExecuted;

		/// <summary>
		/// Access the board of the current game.
		/// </summary>
		public BoardWrapper Board
		{
			get
			{
				return Game.GetBoard();
			}
		}

		public List<KeyValuePair<MoveWrapper, Players>> MoveLog { get; set; }

		public IEnumerable<MoveWrapper> LegalMoves
		{
			get
			{
				return Board.GetLegalMoves(CurrentPlayer);
			}
		}

		/// <summary>
		/// The current state of the current player's move.
		/// </summary>
		public MoveWrapper CurrentMove { get; set; }

		/// <summary>
		/// Current state of the game.
		/// </summary>
		public KaroGame Game { get; set; }

		private MoveWrapper _lastMove { get; set; }

		public KaroGameManager()
		{
			Game = new KaroGame();
			MoveLog = new List<KeyValuePair<MoveWrapper, Players>>();
			Debug.WriteLine("Init Board State: {0}", Board.ToString());
			CurrentState = PlaceState.Instance;
		}

		/// <summary>
		/// Changes the CurrentState to the specified state. The specified state's
		/// Enter method will be called after the CurrentState is updated. The
		/// CurrentState's Exit method will be called before the CurrentState is
		/// updated.
		/// </summary>
		public void ChangeState(IKaroState state)
		{
			if (CurrentState != null)
			{
				CurrentState.Exit(this);
			}
			CurrentState = state;
			CurrentState.Enter(this);
		}

		/// <summary>
		/// Perform actions depending on the current state and the click location.
		/// </summary>
		public virtual void Update(Point tileLocation)
		{
			Debug.WriteLine("Click received at tile {0}.", tileLocation);
			if (CurrentState != null)
			{
				CurrentState.Update(this, tileLocation);
			}
			
		}

		public virtual void ExecuteMove(MoveWrapper move)
		{
			MoveLog.Add(new KeyValuePair<MoveWrapper,Players>(move, CurrentPlayer));
			Debug.WriteLine("TopLeft: {0}", Board.GetRelativeCellAt(new Vector2DWrapper(0, 0)).GetAbsolutePosition());
			Debug.WriteLine("Before Execute Board State: {0}", Board.ToString());
			Game.ExecuteMove(move, CurrentPlayer);
			_lastMove = move;
			SwapCurrentPlayer();
			Debug.WriteLine("After Board State: {0}", Board.ToString());
			if (OnMoveExecuted != null)
			{
				OnMoveExecuted(move);
			}
			if (OnBoardUpdated != null)
			{
				OnBoardUpdated();
			}
		}

		public void UndoLastMove()
		{
			if (_lastMove != null)
			{
				SwapCurrentPlayer();
				Game.UndoMove(_lastMove, CurrentPlayer);
			}
		}

		public void SwapCurrentPlayer()
		{
			// Swap the player to the other player with the ternary operator.
			CurrentPlayer = CurrentPlayer == Players.Max ? Players.Min : Players.Max;
		}
	}
}
