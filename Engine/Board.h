#pragma once

#include "Grid.h"
#include "IBoard.h"
#include "Move.h"

namespace engine{

	enum ENGINE_API TileValue{
		HasTile = 1,
		IsMax = 2,
		IsFlipped = 4
	};

	class ENGINE_API Board : IBoard {
	public:
		Board();
		~Board();

		void ExecuteMove(Move* move, Players player);
		std::vector<Move>* GetLegalMoves(Players player);
	private:
		Grid<TileValue>* _grid;
	};

}