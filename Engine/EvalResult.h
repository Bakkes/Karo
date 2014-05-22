#pragma once

#include "Move.h"

namespace engine {

	class EvalResult {
	public:
		EvalResult();
		EvalResult(const EvalResult& er);
		EvalResult(int bestForMax, int bestForMin);
		~EvalResult();

		EvalResult& operator=(const EvalResult& other);

		void SetScore(int score);
		void SetMove(Move move);
		void SetBestForMax(int bestForMax);
		void SetBestForMin(int bestForMin);

		const int& GetScore() const;
		const Move& GetMove() const;
		int GetBestForMax() const;
		int GetBestForMin() const;
		bool IsSet() const;

	private:
		int _score;
		Move _move;
		int _bestForMax;
		int _bestForMin;
		bool _isSet;
	};
}
