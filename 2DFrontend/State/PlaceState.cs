using System;
using System.Linq;
using System.Collections.Generic;
using System.Drawing;
using engine.wrapper;

namespace _2DFrontend.State
{
	/// <summary>
	/// In this state, a human player can place a piece on an empty tile.
	/// </summary>
	class PlaceState : IKaroState
	{
		private static PlaceState _instance;

		public static IKaroState Instance
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
			IEnumerable<MoveWrapper> legalMoves = manager.LegalMoves;
			MoveWrapper move = legalMoves.FirstOrDefault(m =>
				m.GetToTile() == new Vector2DWrapper(click.X, click.Y));
			// We have a valid move.
			if (move != null)
			{
				manager.ExecuteMove(move);
			}

			// Change state to Piece source state if all 6 pieces are on the board.
			if (manager.Board.GetOccupiedTiles().Count == 6)
			{
				manager.ChangeState(PieceSourceState.Instance);
			}
		}
	}
}
