#include "RandStaticEval.h"

namespace engine {
	RandStaticEval::RandStaticEval() {
		_lowestScore = INT_MAX;
		_highestScore = INT_MIN;
	}

	RandStaticEval::~RandStaticEval()	{
	}

	int RandStaticEval::Eval(IBoard* board, Players player) {
		int score = rand();
		
		if (score > _highestScore) {
			_highestScore = score;
		} else if (score < _lowestScore) {
			_lowestScore = score;
		}

		return score;
	}
}
