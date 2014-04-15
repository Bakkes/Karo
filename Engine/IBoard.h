#pragma once

#include <vector>
#include "Move.h"

namespace engine {
	class IBoard {
	public:
		virtual void ExecuteMove(Move* move) = 0;
		virtual std::vector<Move>* GetLegalMoves() = 0;
	};
}