#include "EvalResult.h"

namespace engine {

	EvalResult::EvalResult(const EvalResult& er) : _move(er._move) {
		_bestForMax = er._bestForMax;
		_bestForMin = er._bestForMin;
		_score = er._score;
		_isSet = er._isSet;
	}

	EvalResult::EvalResult() : _move(INSERT, Vector2D(-1)) {
		_bestForMax = -1337;
		_bestForMin = 1337;
		_score = -1337;
		_isSet = false;
	}

	EvalResult::EvalResult(int bestForMax, int bestForMin) : _move(INSERT, Vector2D(-1)) {
		_isSet = false;
		_bestForMax = bestForMax;
		_bestForMin = bestForMin;
		_score = -1337;
	}

	EvalResult::~EvalResult() {
	}

	EvalResult& EvalResult::operator = (const EvalResult& er) {
		_bestForMax = er._bestForMax;
		_bestForMin = er._bestForMin;
		_score = er._score;
		_isSet = er._isSet;
		_move = er._move;
		return *this; 
	}

	void EvalResult::SetScore(int score) {
		_score = score;
	}

	void EvalResult::SetMove(Move move) {
		_isSet = true;
		_move = move;
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
