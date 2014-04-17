using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using engine.wrapper;

namespace _2DFrontend.State
{
	/// <summary>
	/// In this state, the player will choose an empty tile that will be moved.
	/// </summary>
	class TileSourceState : IKaroState
	{
		private static TileSourceState _instance;

		public static IKaroState Instance
		{
			get
			{
				if (_instance == null)
				{
					_instance = new TileSourceState();
				}
				return _instance;
			}
		}

		/// <summary>
		/// Private constructor for singleton.
		/// </summary>
		private TileSourceState()
		{
		}

		public void Update(KaroGameManager manager, Point click)
		{
			IEnumerable<MoveWrapper> legalMoves = manager.LegalMoves;
			MoveWrapper move = legalMoves.FirstOrDefault(m =>
				m.GetFromTile() == manager.CurrentMove.GetFromTile() &&
				m.GetToTile() == manager.CurrentMove.GetToTile() &&
				m.GetUsedTile() == new Vector2DWrapper(click.X, click.Y));
			if (move != null)
			{
				// We now have a valid move. Execute it!
				manager.ExecuteMove(move);
			}
			else
			{
				// Clicked on invalid tile. Back to PieceSourceState.
				manager.CurrentMove = null;
				manager.ChangeState(PieceSourceState.Instance);
			}
		}
	}
}
