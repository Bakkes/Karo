#pragma once

#include "Move.h"

namespace engine {

	class EvalResult {
	public:
		EvalResult();
		~EvalResult();

		void SetScore(int score);
		void SetMove(Move move);
		void SetLowerBound(int lowerBound);
		void SetUpperBound(int upperBound);

		int GetScore();
		Move GetMove();
		int GetLowerBound();
		int GetUpperBound();
		bool IsSet();

	private:
		int _score;
		Move _move;
		int _lowerBound;
		int _upperBound;
		bool _isSet;
	};
}
