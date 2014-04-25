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
		_isSet = true;
		_move = move;
		_isSet = true;
	}

	void EvalResult::SetBestForMax(int bestForMax) {
		_bestForMax = bestForMax;
	}

	void EvalResult::SetBestForMin(int bestForMin) {
		_bestForMin = bestForMin;
	}

	const int& EvalResult::GetScore() const {
		return _score;
	}

	const Move& EvalResult::GetMove() const {
		return _move;
	}

	int EvalResult::GetBestForMax() {
		return _bestForMax;
	}

	int EvalResult::GetBestForMin() {
		return _bestForMin;
	}

	bool EvalResult::IsSet() {
		return _isSet;
	}
}
