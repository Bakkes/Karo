#include "Board.h"
namespace engine{

	Board::Board(){
		_grid = new Grid<int>();
		_grid->BindTilesToEachother(true);
		_grid->TraverseTiles(
			[](Tile<int>* tile) -> void{
				Size boardSize = Size(5,4); // which tiles to init from 0,0
				int* data = new int(~HasTile);
				if(tile->GetPosition()->X() < boardSize.GetWidth() && tile->GetPosition()->Y() < boardSize.GetHeight()){
					*data |= HasTile | IsEmpty;
				} 
				tile->SetData(data);
			}
		);
	}
	Board::~Board(){
		delete _grid;
	}

	void Board::ExecuteMove(Move *m, Players player) {

	}

	std::vector<Move>* Board::GetLegalMoves(Players player) {
		return new vector<Move>();
	}
	std::vector<Tile<int>>* Board::GetOccupiedTiles(){
		return new vector<Tile<int>>();
	}

	int Board::GetNumberOfEdges(Tile<int>* tile) {
		int edges = 0;

		if (!*tile->GetLeft()->GetData() & IsEmpty == IsEmpty) {
			edges++;
		}
		if (!*tile->GetRight()->GetData() & IsEmpty == IsEmpty) {
			edges++;
		}
		if (!*tile->GetTop()->GetData() & IsEmpty == IsEmpty) {
			edges++;
		}
		if (!*tile->GetBottom()->GetData() & IsEmpty == IsEmpty) {
			edges++;
		}

		return edges;
	}

}