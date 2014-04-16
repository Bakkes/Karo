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
		public IKaroState CurrentState { get; set; }

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

		/// <summary>
		/// The current state of the current player's move.
		/// </summary>
		private MoveWrapper CurrentMove { get; set; }

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
			CurrentState = state;
		}

		/// <summary>
		/// Perform actions depending on the current state and the click location.
		/// </summary>
		public void Update(Point tileLocation)
		{
			if (CurrentState != null)
			{
				CurrentState.Update(this, tileLocation);
			}
		}
	}
}
