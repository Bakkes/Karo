#pragma once

#include <vector>
#include "Players.h"
#include "Move.h"
namespace engine {
	class IBoard {
		virtual void ExecuteMove(Move* move, Players player) = 0;
		virtual std::vector<Move>* GetLegalMoves(Players player) = 0;
	};
}