#include "Result.h"

namespace engine {

	Result::Result(Move* move, int score) {
		_move = move;
		_score = score;
	}

	Result::~Result() {
	}

	Move* Result::GetMove() {
		return _move;
	}

	int Result::GetScore() {
		return _score;
	}
}
