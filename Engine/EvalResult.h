#pragma once

#include "Move.h"

namespace engine {

	class EvalResult {
	public:
		EvalResult();
		~EvalResult();

		void SetScore(int score);
		void SetMove(Move move);

		int GetScore();
		Move GetMove();
		bool IsSet();

	private:
		int _score;
		Move _move;
		bool _isSet;
	};
}
