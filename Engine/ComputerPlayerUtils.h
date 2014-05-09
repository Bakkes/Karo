#pragma once

#include "IBoard.h"
#include "Move.h"
#include "Players.h"

namespace engine {
	class ENGINE_API ComputerPlayerUtils
	{
	public:
		static Move InvertMove(Move move); 
		static Players InvertPlayer(Players player); 
		static bool IsWinningState(IBoard* board);
	};
}
