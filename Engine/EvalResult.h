#pragma once

#include "Move.h"

namespace engine {

	class EvalResult {
	public:
		EvalResult();
		~EvalResult();

		void SetScore(int score);
		void SetMove(Move move);
		void SetBestForMax(int bestForMax);
		void SetBestForMin(int bestForMin);

		int GetScore();
		Move GetMove();
		int GetBestForMax();
		int GetBestForMin();
		bool IsSet();

	private:
		int _score;
		Move _move;
		int _bestForMax;
		int _bestForMin;
		bool _isSet;
	};
}
