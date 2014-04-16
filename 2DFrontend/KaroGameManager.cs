﻿using _2DFrontend.State;
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
		/// The current state of the current player's move.
		/// </summary>
		private MoveWrapper CurrentMove { get; set; }

		/// <summary>
		/// Current state of the game.
		/// </summary>
		private KaroGame Game { get; set; }

		public void ChangeState(IKaroState state)
		{
			CurrentState = state;
		}
	}
}