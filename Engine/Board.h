#include "Grid.h"
#pragma once
namespace karo{

	class Board{
	public:
		Board();
		// assign indexes to each tile
		void Reindex();
	private:
		Grid<int>* _grid;
	};

}