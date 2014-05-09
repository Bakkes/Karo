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
		return false;
	}
}
