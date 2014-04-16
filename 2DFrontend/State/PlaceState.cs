using System;
using System.Drawing;

namespace _2DFrontend.State
{
	/// <summary>
	/// In this state, a human player can place a piece on an empty tile.
	/// </summary>
	class PlaceState : IKaroState
	{
		private IKaroState _instance;

		public IKaroState Instance
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
			throw new NotImplementedException();
		}
	}
}
