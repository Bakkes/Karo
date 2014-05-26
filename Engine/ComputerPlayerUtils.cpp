#include "ComputerPlayerUtils.h"

namespace engine {

	int IsWinningTileFor(const RelativeCell& cell, const Players& player){
		Players playerAtCell = cell.IsMaxPiece() ? Max : Min;
		return cell.HasTile() && (!cell.IsEmpty()) && cell.IsFlipped() && playerAtCell == player;
	}
	Players ComputerPlayerUtils::InvertPlayer(Players player) {
		if (player == Players::Min) {
			return Players::Max;
		}
		return Players::Min;
	}

	bool ComputerPlayerUtils::IsWinningState(IBoard* board, Players player) {
		if (board->GetPieceCountFor(player) < IBoard::MaxPiecesPerPlayer)
			return false;

		if (IsWinningStateHorizontal(board, player))
			return true;

		if (IsWinningStateVertical(board, player))
			return true;

		if (IsWinningStateDiagonalUp(board, player))
			return true;

		if (IsWinningStateDiagonalDown(board, player))
			return true;

		return false;
	}

	bool ComputerPlayerUtils::IsWinningStateHorizontal(IBoard* board, Players player) {
		for (int x = 0; x < 16; ++x) {
			for (int y = 0; y < 20; ++y) {
				RelativeCell cell = board->GetRelativeCellAt(Vector2D(x, y));

				for (int i = 0; i < 4; i++) {
					if (!IsWinningTileFor(board->GetRelativeCellAt(Vector2D(x + i, y)), player)) {
						// Can not be part of 4 flipped pieces
						break;
					}

					if (i == 3) {
						// 4 flipped pieces of the same time in a horizontal row
						return true;
					}
				}
			}
		}
		return false;
	}

	bool ComputerPlayerUtils::IsWinningStateVertical(IBoard* board, Players player) {
		for (int y = 0; y < 16; ++y) {
			for (int x = 0; x < 20; ++x) {
				RelativeCell cell = board->GetRelativeCellAt(Vector2D(x, y));

				for (int i = 0; i < 4; i++) {
					if (!IsWinningTileFor(board->GetRelativeCellAt(Vector2D(x, y+i)), player)) {
						// Can not be part of 4 flipped pieces
						break;
					}

					if (i == 3) {
						// 4 flipped pieces of the same time in a vertical row
						return true;
					}
				}
			}
		}
		return false;
	}

	bool ComputerPlayerUtils::IsWinningStateDiagonalUp(IBoard* board, Players player) {
		for (int y = 3; y < 20; ++y) {
			for (int x = 0; x < 16; ++x) {
				RelativeCell cell = board->GetRelativeCellAt(Vector2D(x, y));

				for (int i = 0; i < 4; i++) {
					if (!IsWinningTileFor(board->GetRelativeCellAt(Vector2D(x + i, y - i)), player)) {
						// Can not be part of 4 flipped pieces
						break;
					}

					if (i == 3) {
						// 4 flipped pieces of the same time in a vertical row
						return true;
					}
				}
			}
		}
		return false;
	}

	bool ComputerPlayerUtils::IsWinningStateDiagonalDown(IBoard* board, Players player) {
		for (int y = 3; y < 20; ++y) {
			for (int x = 3; x < 16; ++x) {
				RelativeCell cell = board->GetRelativeCellAt(Vector2D(x, y));

				for (int i = 0; i < 4; i++) {
					if (!IsWinningTileFor(board->GetRelativeCellAt(Vector2D(x - i, y - i)), player)) {
						// Can not be part of 4 flipped pieces
						break;
					}

					if (i == 3) {
						// 4 flipped pieces of the same time in a vertical row
						return true;
					}
				}
			}
		}
		return false;
	}
}
