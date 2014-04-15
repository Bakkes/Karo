#include "Grid.h"
#include "IBoard.h"
#pragma once
namespace engine{

	class Board : IBoard{
	public:
		Board();
		~Board();
	private:
		Grid<int>* _grid;
	};

}