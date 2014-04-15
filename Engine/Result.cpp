#include "Result.h"

namespace engine {

	Result::Result() : _move(MoveType::DELETE, -1, -1, MoveDirection::NONE, -1) {
	}

	Result::Result(Move move, int score) : _move(MoveType::DELETE, -1, -1, MoveDirection::NONE, -1) {
		_move = move;
		_score = score;
	}

	Result::~Result() {
	}

	Move Result::GetMove() {
		return _move;
	}

	int Result::GetScore() {
		return _score;
	}
}
