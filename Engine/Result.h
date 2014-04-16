#pragma once

#include "Move.h"

namespace engine {
	class Result {
	public:
		Result();
		~Result();

		int GetScore();

	private:
		int _score;
	};
}
