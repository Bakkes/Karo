using System;
using System.Diagnostics;
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
		}

		public void Exit(KaroGameManager manager)
		{
			Debug.WriteLine("Exiting ComputerState...");
		}
	}
}
