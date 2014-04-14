#include "Board.h"
namespace engine{

	Board::Board(){
		_grid = new Grid<TileValue>();
	}
	Board::~Board(){
		delete _grid;
	}

}