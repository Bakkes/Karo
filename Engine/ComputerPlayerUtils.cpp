#include "ComputerPlayerUtils.h"

namespace engine {

	Move ComputerPlayerUtils::InvertMove(Move move) {
		switch (move.GetMoveType()) {
		case INSERT:
			return Move(DELETE, move.GetToCell());
		case MOVE: {
			if (move.HasUsedCell()) {
				return Move(MOVE, move.GetUsedCell(), move.GetFromCell(), move.GetToCell());
			} else {
				return Move(MOVE, move.GetToCell(), move.GetFromCell());
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
}
