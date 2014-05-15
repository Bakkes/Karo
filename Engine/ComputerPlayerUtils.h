#pragma once

#include "IBoard.h"
#include "Move.h"
#include "Players.h"

namespace engine {
	class ENGINE_API ComputerPlayerUtils
	{
	public:
		static Players InvertPlayer(Players player); 
		static bool IsWinningState(IBoard* board, Players player);

	private:
		static bool IsWinningStateHorizontal(IBoard* board, Players player);
		static bool IsWinningStateVertical(IBoard* board, Players player);
		static bool IsWinningStateDiagonalUp(IBoard* board, Players player);
		static bool IsWinningStateDiagonalDown(IBoard* board, Players player);
	};
}
