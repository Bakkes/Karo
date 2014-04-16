using System;
using System.Drawing;

namespace _2DFrontend.State
{
	/// <summary>
	/// In this state, the player will decide on which tile he wants to move
	/// his piece to. If clicked on a non valid tile, the game will go back to
	/// the PieceSourceState.
	/// </summary>
	class PieceDestinationState : IKaroState
	{
		private PieceDestinationState _instance;

		public IKaroState Instance
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
			throw new NotImplementedException();
		}
	}
}
