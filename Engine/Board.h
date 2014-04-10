#include "Grid.h"
#pragma once
namespace karo{

	class Board{
	public:
		Board();
		~Board();
		// assign indexes to each tile
		void ReIndex();
	private:
		Grid<int>* _grid;
	};

}