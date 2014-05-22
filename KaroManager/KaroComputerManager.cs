using engine.wrapper;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

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
            base.ExecuteMove(move);
            Game.ExecuteMove(Game.GetBestMove(),CurrentPlayer);
            SwapCurrentPlayer();
            Debug.WriteLine("After Board State: {0}", Board.ToString());
        }
    }
}
