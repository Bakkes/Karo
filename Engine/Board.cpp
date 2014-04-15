#include "Board.h"
namespace engine{

	Board::Board(){
		_grid = new Grid<TileValue>();
	}
	Board::~Board(){
		delete _grid;
	}

	void Board::ExecuteMove(Move *m, Players player) {

	}

	std::vector<Move>* Board::GetLegalMoves(Players player) {
		return new vector<Move>();
	}

}