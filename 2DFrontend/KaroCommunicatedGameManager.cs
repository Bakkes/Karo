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
	class KaroCommunicatedGameManager : KaroGameManager
	{
		private ICommunication _communication;
		public KaroCommunicatedGameManager(ICommunication communication)
			: base()
		{
			CurrentPlayer = Players.Min;
			_communication = communication;
			_communication.Connected += _communication_Connected;
			_communication.Disconnected += _communication_Disconnected;
			_communication.RequestFirstMove += communication_RequestFirstMove;
			_communication.SentMoveInvalid += _communication_SentMoveInvalid;
			_communication.TurnReceived += _communication_TurnReceived;
			_communication.WinAccepted += _communication_WinAccepted;
			_communication.WinDetected += _communication_WinDetected;
			_communication.WinRejected += _communication_WinRejected;
			
		}

		void _communication_WinRejected()
		{
			Debug.WriteLine("Opponent did not accept win.");
		}

		void _communication_WinDetected(Turn t, Player p)
		{
			if (p == Player.You)
			{
				Debug.WriteLine("Opponent thinks he won, going to check.");
				if (Game.HasWon(Players.Min))
				{
					Debug.WriteLine("Opponent did win, we lose.");
					_communication.SendWinAccepted();
				}
				else
				{
					Debug.WriteLine("Opponent thinks he won but didnt according to us.");
					_communication.SendWinDisputed();
				}
			}
			else if (p == Player.Me)
			{
				Debug.WriteLine("Opponent thinks I won, going to check.");
				if (Game.HasWon(Players.Max))
				{
					Debug.WriteLine("We actually won without noticing?");
					_communication.SendWinAccepted();
				}
				else
				{
					Debug.WriteLine("We didnt win according to our calculations.");
					_communication.SendWinDisputed();
				}
			}
		}

		void _communication_WinAccepted()
		{
			Debug.WriteLine("We won!");
		}

		void _communication_TurnReceived(Turn t)
		{

			Debug.WriteLine("Opponent took a turn");
			if (t == null)
			{
				Console.WriteLine("Turn is null, sending back");
				_communication.SendMoveInvalid(t);
				return;
			}
			Debug.WriteLine("Received turn: " + TurnToString(t));
			MoveWrapper received = ConvertTurnToMove(t);
			Debug.WriteLine("Converted turn to move: " + MoveWrapperToString(received));

			// Get the move with the correct source tile from the last click.
			MoveWrapper mv = LegalMoves.Where(m =>
				m.GetFromCell() == received.GetFromCell() && 
				m.GetToCell() == received.GetToCell() &&
				(!m.HasUsedCell() || m.GetUsedCell() == received.GetUsedCell())).FirstOrDefault();

			if (mv == null)
			{
				Console.WriteLine("Move is illegal, sending back");
				_communication.SendMoveInvalid(t);
				return;
			}
			ExecuteMove(mv);
			//Handled their move, moving on to ours now


			MoveWrapper bm = Game.GetBestMove();
			ExecuteMove(bm);
			if (Game.HasWon(Players.Max))
			{
				Debug.WriteLine("We won, sending message to opponent.");
				_communication.SendWinDetected(Player.Me, ConvertMoveToTurn(bm));
			}
			else
			{
				Debug.WriteLine("Move made, sending move to opponent.");
				_communication.SendTurn(ConvertMoveToTurn(bm));
			}
			Debug.WriteLine("Move sent to opponent: " + MoveWrapperToString(bm));
			Debug.WriteLine("Converted move to turn: " + TurnToString(ConvertMoveToTurn(bm)));
		}

		void _communication_SentMoveInvalid(Turn t)
		{
			Debug.WriteLine("Opponent says our move is wrong.");
		}

		void communication_RequestFirstMove()
		{
			Debug.WriteLine("We're first.");
			CurrentPlayer = Players.Max;
			MoveWrapper bm = Game.GetBestMove();
			ExecuteMove(bm);
			_communication.SendTurn(ConvertMoveToTurn(bm));
			Debug.WriteLine("Move sent to opponent: " + MoveWrapperToString(bm));
			Debug.WriteLine("Converted move to turn: " + TurnToString(ConvertMoveToTurn(bm)));
		}

		void _communication_Disconnected(DisconnectReason reason)
		{
			Debug.WriteLine("Opponent disconnected, reason: " + reason.ToString());

		}

		void _communication_Connected()
		{
			Debug.WriteLine("Connected to opponent, GLHF");
		}

		public override void Update(System.Drawing.Point tileLocation)
		{
			
		}

		private Vector2DWrapper CalculateToCell(Turn t)
		{
			BoardWrapper b = Game.GetBoard();
			Vector2DWrapper fromPosition = ConvertIntToBoardPosition(t.FromTile);
			int moveSize = t.MoveType == CommunicationProtocol.MoveType.Jump ? 2 : 1;

			switch (t.Direction)
			{
				case Direction.None:
					break;
				case Direction.North:
					fromPosition.X -= moveSize;
					break;
				case Direction.East:
					fromPosition.Y += moveSize;
					break;
				case Direction.South:
					fromPosition.X += moveSize;
					break;
				case Direction.West:
					fromPosition.Y -= moveSize;
					break;
				case Direction.NorthEast:
					fromPosition.X -= moveSize;
					fromPosition.Y += moveSize;
					break;
				case Direction.NorthWest:
					fromPosition.X -= moveSize;
					fromPosition.Y -= moveSize;
					break;
				case Direction.SouthEast:
					fromPosition.X += moveSize;
					fromPosition.Y += moveSize;
					break;
				case Direction.SouthWest:
					fromPosition.X += moveSize;
					fromPosition.Y -= moveSize;
					break;
			}

			return fromPosition;
		}

		private MoveWrapper ConvertTurnToMove(Turn t)
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

		private Vector2DWrapper ConvertIntToBoardPosition(int? number)
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
            for (int x = 0; x < 20; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    CellWrapper cell = Board.GetRelativeCellAt(new Vector2DWrapper(x, y));
                    if ((cell.GetData() & (int)CellValue.IsEmpty) == 0)
                    {
                        continue;
                    }

                    // This cell has a tile, increment the number
                    currentNumber++;
                    if (currentNumber == number)
                    {
                        return new Vector2DWrapper(x, y);
                    }
                }
            }

            throw new Exception("Failed to translate int to board position");
		}

		private int ConvertBoardPositionToInt(Vector2DWrapper vector2D)
		{
            int number = 0;
            for (int x = 0; x < 20; x++)
            {
                for (int y = 0; y < 20; y++)
                {
                    CellWrapper cell = Board.GetRelativeCellAt(new Vector2DWrapper(x, y));
					bool reachedEnd = x == vector2D.X && y == vector2D.Y;

                    if ((cell.GetData() & (int)CellValue.IsEmpty) == 0)
                    {
						if (reachedEnd)
						{
							return number;
						}
                        continue;
                    }

                    // There is a tile here, update the number
                    number++;

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

		private Turn ConvertMoveToTurn(MoveWrapper mw)
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
			t.FromTile = ConvertBoardPositionToInt(mw.GetFromCell());
			return t;
		}

		public static String MoveWrapperToString(MoveWrapper mw)
		{
			return String.Format("MOVE: Type {0}, FTU: {1},{2},{3}", mw.GetMoveType(), mw.GetFromCell(), mw.GetToCell(), mw.GetUsedCell());
		}

		public static String TurnToString(Turn t)
		{
			return String.Format("TURN: Type: {0}, FDU: {1},{2},{3}", t.MoveType, t.FromTile, t.Direction, t.EmptyTile);
		}

	}
}
