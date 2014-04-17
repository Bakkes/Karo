using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using _2DFrontend.State;
using engine.wrapper;

namespace _2DFrontend
{
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
		public Players CurrentPlayer { get; private set; }

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
		private KaroGame Game { get; set; }

		public KaroGameManager()
		{
			Game = new KaroGame();
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
		public void Update(Point tileLocation)
		{
			Debug.WriteLine("Click received at tile {0}.", tileLocation);
			if (CurrentState != null)
			{
				CurrentState.Update(this, tileLocation);
			}
		}

		public void ExecuteMove(MoveWrapper move)
		{
			Game.ExecuteMove(move, CurrentPlayer);
			SwapCurrentPlayer();
		}

		private void SwapCurrentPlayer()
		{
			// Swap the player to the other player with the ternary operator.
			CurrentPlayer = CurrentPlayer == Players.Max ? Players.Min : Players.Max;
		}
	}
}
