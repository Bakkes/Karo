#include "Board.h"
namespace engine{

	Board::Board(){
		_grid = new Grid<int>();
	}
	Board::~Board(){
		delete _grid;
	}

}