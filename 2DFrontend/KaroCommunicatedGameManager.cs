using CommunicationProtocol;
using engine.wrapper;
using System;
using System.Collections.Generic;
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
			Console.WriteLine("Opponent did not accept win.");
		}

		void _communication_WinDetected(Turn t, Player p)
		{
			if (p == Player.You)
			{
				if (Game.HasWon(Players.Min))
				{
					_communication.SendWinAccepted();
				}
				else
				{
					_communication.SendWinDisputed();
				}
			}
			else if (p == Player.Me)
			{
				if (Game.HasWon(Players.Max))
				{
					_communication.SendWinAccepted();
				}
				else
				{
					_communication.SendWinDisputed();
				}
			}
			Console.WriteLine("Opponent thinks he won, going to check.");
		}

		void _communication_WinAccepted()
		{
			Console.WriteLine("We won!");
		}

		void _communication_TurnReceived(Turn t)
		{
			Console.WriteLine("Opponent took a turn");
			MoveWrapper received = ConvertTurnToMove(t);

			// Get the move with the correct source tile from the last click.
			MoveWrapper mv = LegalMoves.Where(m =>
				m.GetFromCell() == received.GetFromCell() && 
				m.GetToCell() == received.GetToCell() &&
				m.GetUsedCell() == received.GetUsedCell()).FirstOrDefault();
			if (mv == null)
			{
				_communication.SendMoveInvalid(t);
				return;
			}
			ExecuteMove(mv);
			//Handled their move, moving on to ours now


			MoveWrapper bm = Game.GetBestMove();
			ExecuteMove(bm);
			if (Game.HasWon(Players.Max))
			{
				_communication.SendWinDetected(Player.Me, ConvertMoveToTurn(bm));
			}
			else
			{
				_communication.SendTurn(ConvertMoveToTurn(bm));
			}
		}

		void _communication_SentMoveInvalid(Turn t)
		{
			Console.WriteLine("Opponent says our move is wrong.");
		}

		void communication_RequestFirstMove()
		{
			Console.WriteLine("We're first.");
			CurrentPlayer = Players.Max;
			MoveWrapper bm = Game.GetBestMove();
			ExecuteMove(bm);
			_communication.SendTurn(ConvertMoveToTurn(bm));
		}

		void _communication_Disconnected(DisconnectReason reason)
		{
			Console.WriteLine("Opponent disconnected, reason: " + reason.ToString());

		}

		void _communication_Connected()
		{
			Console.WriteLine("Connected to opponent, GLHF");
		}

		public override void Update(System.Drawing.Point tileLocation)
		{
			
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
					mt = engine.wrapper.MoveType.MOVE;
					break;
			}
			return new MoveWrapper(mt, ConvertIntToBoardPosition(t.FromTile),
				ConvertIntToBoardPosition(t.ToTile), ConvertIntToBoardPosition(t.EmptyTile));
		}

		private Vector2DWrapper ConvertIntToBoardPosition(int? number)
		{
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
            for (int x = 0; x <= vector2D.X; x++)
            {
                for (int y = 0; y <= vector2D.Y; y++)
                {
                    CellWrapper cell = Board.GetRelativeCellAt(new Vector2DWrapper(x, y));
                    if ((cell.GetData() & (int)CellValue.IsEmpty) == 0)
                    {
                        continue;
                    }

                    // There is a tile here, update the number
                    number++;
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
				case engine.wrapper.MoveType.MOVE:
					mt = CommunicationProtocol.MoveType.Move;
					break;
			}
			Turn t = new Turn();
			t.MoveType = mt;
			t.EmptyTile = ConvertBoardPositionToInt(mw.GetUsedCell());
			t.FromTile = ConvertBoardPositionToInt(mw.GetFromCell());
			t.ToTile = ConvertBoardPositionToInt(mw.GetToCell());
			return t;
		}

	}
}
