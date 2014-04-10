#pragma once
#include "Move.h"
#include "IUnsafeBoard.h"
#include <vector>
namespace Engine {
	class IBoard {
	public:
		virtual void ExecuteMove(Move* move) = 0;
		virtual std::vector<Move*> GetLegalMoves() = 0;
		virtual IUnsafeBoard GetUnsafeBoard() = 0;
	};

}