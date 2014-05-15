#include "ComputerPlayerUtils.h"

namespace engine {

	Players ComputerPlayerUtils::InvertPlayer(Players player) {
		if (player == Players::Min) {
			return Players::Max;
		}
		return Players::Min;
	}

	bool ComputerPlayerUtils::IsWinningState(IBoard* board) {
		if (board->GetPieceCountFor(Max) < IBoard::MaxPiecesPerPlayer && board->GetPieceCountFor(Min) < IBoard::MaxPiecesPerPlayer)
			return false;

		if (IsWinningStateHorizontal(board))
			return true;

		if (IsWinningStateVertical(board))
			return true;

		if (IsWinningStateDiagonalUp(board))
			return true;

		if (IsWinningStateDiagonalDown(board))
			return true;

		return false;
	}

	bool ComputerPlayerUtils::IsWinningStateHorizontal(IBoard* board) {
		for (int x = 0; x < 16; ++x) {
			for (int y = 0; y < 20; ++y) {
				RelativeCell cell = board->GetRelativeCellAt(Vector2D(x, y));
				Players player = cell.IsMaxPiece() ? Max : Min;

				for (int i = 0; i < 4; i++) {
					Players playerAtCell = cell.IsMaxPiece() ? Max : Min;
					if (!cell.HasTile() || !cell.IsFlipped() || playerAtCell != player) {
						// Can not be part of 4 flipped pieces
						break;
					}

					if (i == 3) {
						// 4 flipped pieces of the same time in a horizontal row
						return true;
					}

					cell = board->GetRelativeCellAt(Vector2D(x + i, y));
				}
			}
		}
		return false;
	}

	bool ComputerPlayerUtils::IsWinningStateVertical(IBoard* board) {
		for (int y = 0; y < 16; ++y) {
			for (int x = 0; x < 20; ++x) {
				RelativeCell cell = board->GetRelativeCellAt(Vector2D(x, y));
				Players player = cell.IsMaxPiece() ? Max : Min;

				for (int i = 0; i < 4; i++) {
					Players playerAtCell = cell.IsMaxPiece() ? Max : Min;
					if (!cell.HasTile() || !cell.IsFlipped() || playerAtCell != player) {
						// Can not be part of 4 flipped pieces
						break;
					}

					if (i == 3) {
						// 4 flipped pieces of the same time in a vertical row
						return true;
					}

					cell = board->GetRelativeCellAt(Vector2D(x, y + i));
				}
			}
		}
		return false;
	}

	bool ComputerPlayerUtils::IsWinningStateDiagonalUp(IBoard* board) {
		return false;
	}

	bool ComputerPlayerUtils::IsWinningStateDiagonalDown(IBoard* board) {
		return false;
	}
}
