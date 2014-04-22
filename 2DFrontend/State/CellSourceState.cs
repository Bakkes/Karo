using System;
using System.Drawing;

namespace _2DFrontend.State
{
	/// <summary>
	/// In this state, the player will choose an empty tile that will be moved.
	/// </summary>
	class CellSourceState : IKaroState
	{
		private static CellSourceState _instance;

		public static IKaroState Instance
		{
			get
			{
				if (_instance == null)
				{
					_instance = new CellSourceState();
				}
				return _instance;
			}
		}

		/// <summary>
		/// Private constructor for singleton.
		/// </summary>
		private CellSourceState()
		{
		}

		public void Update(KaroGameManager manager, Point click)
		{
			throw new NotImplementedException();
		}
	}
}
