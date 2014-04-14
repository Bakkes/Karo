#include "Board.h"
namespace engine{

	Board::Board(){
		_grid = new Grid<Tile<TileValue>>();
	}
	Board::~Board(){
		delete _grid;
	}

}