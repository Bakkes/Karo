#pragma once

#include <vector>

namespace engine {
	class IBoard {
	public:
		virtual void ExecuteMove(Move* move) = 0;
		virtual std::vector<Move>* GetLegalMoves() = 0;
	};
}