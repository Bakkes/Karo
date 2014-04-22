#pragma once

#include "DllImportExport.h"
#include "IBoard.h"
#include "Players.h"
#include "Move.h"

namespace engine{
	class ENGINE_API MoveFinder
	{
	public:
		MoveFinder(IBoard* board);
		~MoveFinder(void);
		std::vector<Move>* GetLegalMoves(Players player);
		std::vector<Move> FindMove(Cell<int>, Cell<int>);
	private:
		IBoard* _board;
	};
}