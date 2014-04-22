#pragma once

#include "DllImportExport.h"
#include "IBoard.h"
#include "Move.h"

namespace engine{
	class ENGINE_API MoveFinder
	{
	public:
		MoveFinder(IBoard* board);
		~MoveFinder(void);
		std::vector<Move> FindMove(Tile<int>,Tile<int>);
	private:
		IBoard* _board;
	};
}