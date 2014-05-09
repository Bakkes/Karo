using CommunicationProtocol;
using engine.wrapper;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2DFrontend
{
	class CommunicationProtocolConversionUtility
	{
		private KaroGame _game;
		private readonly Dictionary<string, Direction> _directions = new Dictionary<string, Direction>() 
			{
				{"" , Direction.None},
				{"N" , Direction.North},
				{"E" , Direction.East},
				{"S" , Direction.South},
				{"W" , Direction.West},
				{"NE" , Direction.NorthEast},
				{"NW" , Direction.NorthWest},
				{"SE" , Direction.SouthEast},
				{"SW" , Direction.SouthWest}
			};

		public CommunicationProtocolConversionUtility(KaroGame game)
		{
			_game = game;
		}

		public Vector2DWrapper CalculateToCell(Turn t)
		{
			BoardWrapper b = _game.GetBoard();
			Vector2DWrapper goalPosition = ConvertIntToBoardPosition(t.FromTile);
			int moveSize = t.MoveType == CommunicationProtocol.MoveType.Jump ? 2 : 1;

			switch (t.Direction)
			{
				case Direction.None:
					break;
				case Direction.North:
					goalPosition.X -= moveSize;
					break;
				case Direction.East:
					goalPosition.Y += moveSize;
					break;
				case Direction.South:
					goalPosition.X += moveSize;
					break;
				case Direction.West:
					goalPosition.Y -= moveSize;
					break;
				case Direction.NorthEast:
					goalPosition.X -= moveSize;
					goalPosition.Y += moveSize;
					break;
				case Direction.NorthWest:
					goalPosition.X -= moveSize;
					goalPosition.Y -= moveSize;
					break;
				case Direction.SouthEast:
					goalPosition.X += moveSize;
					goalPosition.Y += moveSize;
					break;
				case Direction.SouthWest:
					goalPosition.X += moveSize;
					goalPosition.Y -= moveSize;
					break;
			}

			return goalPosition;
		}

		public Direction CalculateDirection(Vector2DWrapper to, Vector2DWrapper from)
		{
			Vector2DWrapper difference = new Vector2DWrapper(from.X - to.X, from.Y - to.Y);
			string xDiff = difference.X == 0 ? "" : difference.X > 0 ? "W" : "E";
			string yDiff = difference.Y == 0 ? "" : difference.Y > 0 ? "N" : "S";
			Debug.WriteLine(yDiff + xDiff +" - " + _directions[yDiff + xDiff]);
			return _directions[yDiff + xDiff];
		}

		public Turn ConvertMoveToTurn(MoveWrapper mw)
		{
			CommunicationProtocol.MoveType mt = CommunicationProtocol.MoveType.Insert;
			switch (mw.GetMoveType())
			{
				case engine.wrapper.MoveType.INSERT:
					mt = CommunicationProtocol.MoveType.Insert;
					break;
				case engine.wrapper.MoveType.JUMP:
					mt = CommunicationProtocol.MoveType.Jump;
					break;
				case engine.wrapper.MoveType.STEP:
					mt = CommunicationProtocol.MoveType.Move;
					break;
			}

			Turn t = new Turn();
			t.MoveType = mt;
			if (mw.HasUsedCell())
			{
				t.EmptyTile = ConvertBoardPositionToInt(mw.GetUsedCell());
			}
			else
			{
				t.EmptyTile = null;
			}

			if (mw.GetMoveType() == engine.wrapper.MoveType.INSERT)
			{
				t.FromTile = ConvertBoardPositionToInt(mw.GetToCell());
				t.Direction = Direction.None;
			}
			else
			{
				t.FromTile = ConvertBoardPositionToInt(mw.GetFromCell());
				t.Direction = CalculateDirection(mw.GetToCell(), mw.GetFromCell());
			}

			return t;
		}


		public MoveWrapper ConvertTurnToMove(Turn t)
		{
			engine.wrapper.MoveType mt = engine.wrapper.MoveType.INSERT;
			switch (t.MoveType)
			{
				case CommunicationProtocol.MoveType.Insert:
					mt = engine.wrapper.MoveType.INSERT;
					break;
				case CommunicationProtocol.MoveType.Jump:
					mt = engine.wrapper.MoveType.JUMP;
					break;
				case CommunicationProtocol.MoveType.Move:
					mt = engine.wrapper.MoveType.STEP;
					break;
			}

			Vector2DWrapper toCell = CalculateToCell(t);

			if (t.EmptyTile == null)
			{
				return new MoveWrapper(mt, ConvertIntToBoardPosition(t.FromTile),
					toCell);
			}
			else
			{
				return new MoveWrapper(mt, ConvertIntToBoardPosition(t.FromTile),
					toCell, ConvertIntToBoardPosition(t.EmptyTile));
			}
		}

		public Vector2DWrapper ConvertIntToBoardPosition(int? number)
		{
			if (number == null)
			{
				return new Vector2DWrapper(0, 0);
			}

			if (number < 0 || number > 20)
			{
				throw new ArgumentException(String.Format("Number {0} can not exist on the board"));
			}

			int currentNumber = 0;
			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					
					CellWrapper cell = _game.GetBoard().GetRelativeCellAt(new Vector2DWrapper(x, y));
					if ((cell.GetData() & (int)CellValue.HasCell) == 1)
					{
						// This cell has a tile, increment the number
						currentNumber++;
						if (currentNumber == number)
						{
							return new Vector2DWrapper(x, y);
						}
					}
				}
			}

			throw new Exception("Failed to translate int to board position");
		}

		public int ConvertBoardPositionToInt(Vector2DWrapper vector2D)
		{
			int number = 0;
			for (int y = 0; y < 20; y++)
			{
				for (int x = 0; x < 20; x++)
				{
					CellWrapper cell = _game.GetBoard().GetRelativeCellAt(new Vector2DWrapper(x, y));
					bool reachedEnd = x == vector2D.X && y == vector2D.Y;
					

					if (cell.HasTile() != 0)
					{
						number++;
					}
					if (reachedEnd)
					{
						return number;
					}
				}
			}

			if (number == 0)
			{
				throw new Exception("No tiles found before this position, invalid position to relate from");
			}

			return number;
		}

		public String MoveWrapperToString(MoveWrapper mw)
		{
			return String.Format("MOVE: Type {0}, FTU: {1},{2},{3}", mw.GetMoveType(), mw.GetFromCell(), mw.GetToCell(), mw.GetUsedCell());
		}

		public String TurnToString(Turn t)
		{
			return String.Format("TURN: Type: {0}, FDU: {1},{2},{3}", t.MoveType, t.FromTile, t.Direction, t.EmptyTile);
		}
	}
}
