using System;
using System.Drawing;

namespace _2DFrontend.State
{
	/// <summary>
	/// In this state, the computer will generate and place a move.
	/// </summary>
	class ComputerState : IKaroState
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

		public void Update(KaroGameManager manager, Point click)
		{
			throw new NotImplementedException();
		}
	}
}
