using System.Diagnostics;
using engine.wrapper;
using KaroManager.State;

namespace KaroManager
{
	public class KaroComputerManager : KaroGameManager
	{

		public KaroComputerManager()
			: base()
		{
		}

		public override void ExecuteMove(engine.wrapper.MoveWrapper move)
		{
			Debug.WriteLine("ComputerExecute Move");
			Debug.WriteLine("TopLeft: {0}", Board.GetRelativeCellAt(new Vector2DWrapper(0, 0)).GetAbsolutePosition());
			Debug.WriteLine("Before Execute Board State: {0}", Board.ToString());
			CurrentMove = null;
			base.ExecuteMove(move);
			ChangeState(WaitForUndoState.Instance);
			Debug.WriteLine("After Board State: {0}", Board.ToString());
		}
	}
}
