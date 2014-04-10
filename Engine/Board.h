#include "Grid.h"
#pragma once
namespace engine{

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