#pragma once

#include "Move.h"

namespace engine {
	class Result {
	public:
		Result();
		Result(Move move, int score);
		~Result();

		Move GetMove();
		int GetScore();

	private:
		Move _move;
		int _score;
	};
}
