#include "Board.h"
namespace karo{

	Board::Board(){
		_grid = new Grid<int>();
	}
	Board::~Board(){
		delete _grid;
	}

}