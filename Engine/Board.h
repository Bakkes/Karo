#include "Grid.h"
#pragma once
namespace engine{

	enum TileValue{
		HasTile = 1,
		IsMax = 2,
		IsFlipped = 4
	};
	class Board{
	public:
		Board();
		~Board();
	private:
		Grid<TileValue>* _grid;
	};

}