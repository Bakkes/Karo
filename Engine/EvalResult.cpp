#include "EvalResult.h"

namespace engine {

	EvalResult::EvalResult() : _move(INSERT, Vector2D(-1)) {
		_isSet = false;
	}

	EvalResult::~EvalResult() {
	}

	void EvalResult::SetScore(int score) {
		_score = score;
	}

	void EvalResult::SetMove(Move move) {
		_move = move;
	}

	int EvalResult::GetScore() {
		_isSet = true;
		return _score;
	}

	Move EvalResult::GetMove() {
		return _move;
	}

	bool EvalResult::IsSet() {
		return _isSet;
	}
}