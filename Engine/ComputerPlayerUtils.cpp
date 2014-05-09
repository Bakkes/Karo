#include "ComputerPlayerUtils.h"

namespace engine {

	Move ComputerPlayerUtils::InvertMove(Move move) {
		switch (move.GetMoveType()) {
		case INSERT:
			return Move(DELETE, move.GetToCell());
		case STEP: {
			if (move.HasUsedCell()) {
				return Move(STEP, move.GetUsedCell(), move.GetFromCell(), move.GetToCell());
			} else {
				return Move(STEP, move.GetToCell(), move.GetFromCell());
			}
		}
		case JUMP: {
			if (move.HasUsedCell()) {
				return Move(JUMP, move.GetUsedCell(), move.GetFromCell(), move.GetToCell());
			} else {
				return Move(JUMP, move.GetToCell(), move.GetFromCell());
			}
		}
		}

		return Move(INSERT, Vector2D(-1,-1));
	}

	Players ComputerPlayerUtils::InvertPlayer(Players player) {
		if (player == Players::Min) {
			return Players::Max;
		}
		return Players::Min;
	}

	bool ComputerPlayerUtils::IsWinningState(IBoard* board) {
		if (board->GetPieceCountFor(Max) < IBoard::MaxPiecesPerPlayer && board->GetPieceCountFor(Min) < IBoard::MaxPiecesPerPlayer)
			return false;

		for (int x = 0; x < 20; ++x) {
			for (int y = 0; y < 20; ++y) {
				RelativeCell cell = board->GetRelativeCellAt(Vector2D(x, y));
				Players player = cell.IsMaxPiece() ? Max : Min;

				for (int i = 0; i < 4; i++) {
					Players playerAtCell = cell.IsMaxPiece() ? Max : Min;
					if (!cell.HasTile() || !cell.IsFlipped()/* || TODO player check */ ) {
						// Can not be part of 4 flipped pieces
						break;
					}
				}


			}
		}

		return false;
	}
}
