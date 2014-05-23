using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using engine.wrapper;

namespace KaroManager.State
{
	/// <summary>
	/// In this state, the player will choose an empty tile that will be moved.
	/// </summary>
	public class CellSourceState : IKaroState
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
			IEnumerable<MoveWrapper> legalMoves = manager.LegalMoves;
			MoveWrapper move = legalMoves.FirstOrDefault(m =>
				m.GetFromCell() == manager.CurrentMove.GetFromCell() &&
				m.GetToCell() == manager.CurrentMove.GetToCell() &&
				m.HasUsedCell() &&
				m.GetUsedCell() == new Vector2DWrapper(click.X, click.Y));
			if (move != null)
			{
				CommunicationProtocolConversionUtility util = new CommunicationProtocolConversionUtility(manager.Game);
				//Debug.WriteLine(util.MoveWrapperToString(move));
				Debug.WriteLine(util.TurnToString(util.ConvertMoveToTurn(move)));
				// We now have a valid move. Execute it!
				Debug.WriteLine("Clicked on moveable tile.");
				manager.ExecuteMove(move);
				manager.CurrentMove = null;
				manager.ChangeState(PieceSourceState.Instance);
			}
			else
			{
				// Clicked on invalid tile. Back to PieceSourceState.
				Debug.WriteLine("Clicked on a non moveable tile.");
				manager.CurrentMove = null;
				manager.ChangeState(PieceSourceState.Instance);
			}
		}

		public void Enter(KaroGameManager manager)
		{
			Debug.WriteLine("Entering TileSourceState...");
		}

		public void Exit(KaroGameManager manager)
		{
			Debug.WriteLine("Exiting TileSourceState...");
		}
	}
}
