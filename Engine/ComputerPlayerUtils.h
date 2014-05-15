#pragma once

#include "IBoard.h"
#include "Move.h"
#include "Players.h"

namespace engine {
	class ENGINE_API ComputerPlayerUtils
	{
	public:
		static Players InvertPlayer(Players player); 
		static bool IsWinningState(IBoard* board);

	private:
		static bool IsWinningStateHorizontal(IBoard* board);
		static bool IsWinningStateVertical(IBoard* board);
		static bool IsWinningStateDiagonalUp(IBoard* board);
		static bool IsWinningStateDiagonalDown(IBoard* board);
	};
}
