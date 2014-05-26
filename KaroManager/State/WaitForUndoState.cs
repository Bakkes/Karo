using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Timers;

namespace KaroManager.State
{
	class WaitForUndoState : IKaroState
	{
		private static WaitForUndoState _instance;

		public static IKaroState Instance
		{
			get
			{
				if (_instance == null)
				{
					_instance = new WaitForUndoState();
				}
				return _instance;
			}
		}

		private Timer _timer;

		public void Enter(KaroGameManager manager)
		{
			_timer = new Timer();
			_timer.Elapsed += delegate { Finished(manager); }; ;
			_timer.AutoReset = true;
			_timer.Interval = 1000;
			_timer.Start();
		}

		public void Update(KaroGameManager manager, System.Drawing.Point click)
		{
			manager.UndoLastMove();
			if (manager.Board.GetOccupiedCells().Count == 6)
			{
				manager.ChangeState(PieceSourceState.Instance);
			}
			else
			{
				manager.ChangeState(PlaceState.Instance);
			}
		}

		public void Exit(KaroGameManager manager)
		{
			_timer.Stop();
		}

		private void Finished(KaroGameManager manager)
		{
			_timer.Stop();
			manager.ChangeState(ComputerState.Instance);
		}
	}
}
