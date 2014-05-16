using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using _2DFrontend.State;
using engine.wrapper;

namespace _2DFrontend
{

	public delegate void BoardUpdated();

	/// <summary>
	/// Statemachine that keeps track of the game's states.
	/// </summary>
	class KaroGameManager
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

		public KaroGameManager()
		{
			Game = new KaroGame();
			Debug.WriteLine("Init Board State: {0}", Board.ToString());
			CurrentState = PlaceState.Instance;
		}

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

		public void ExecuteMove(MoveWrapper move)
		{
			Debug.WriteLine("TopLeft: {0}", Board.GetRelativeCellAt(new Vector2DWrapper(0, 0)).GetAbsolutePosition());
			Debug.WriteLine("Before Execute Board State: {0}", Board.ToString());
			Game.ExecuteMove(move, CurrentPlayer);
			SwapCurrentPlayer();
			Debug.WriteLine("After Board State: {0}", Board.ToString());
		}

		private void SwapCurrentPlayer()
		{
			// Swap the player to the other player with the ternary operator.
			CurrentPlayer = CurrentPlayer == Players.Max ? Players.Min : Players.Max;
		}
	}
}
