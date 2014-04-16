#include "Board.h"
namespace engine{

	Board::Board(){
		_grid = new Grid<int>();
		_grid->BindTilesToEachother(true);
		_grid->TraverseTiles(
			[](Tile<int>* tile) -> void{
				Size boardSize = Size(5,4); // which tiles to init from 0,0
				int* data = new int(0);
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
		auto tiles = new vector<Tile<int>>();
		_grid->TraverseTiles(
			[&](Tile<int>* tile) -> void{
				if(!*tile->GetData() & HasTile){
					return;
				}
				if(*tile->GetData() & IsEmpty){
					return;
				}
				tiles->push_back(*tile);
			}
		);
		return tiles;
	}
	std::string Board::ToString(){
		std::string result = "";
		_grid->TraverseTiles(
			[&, this](Tile<int>* tile) -> void{
				if(tile->GetPosition()->X() +1 == this->_grid->GetSize()->GetWidth()){
					result += "\r\n";
				}
				int data = *tile->GetData();
				result += *tile->GetData() + ",";
			}
		);
		return result;
		
	}
	Tile<int>* Board::GetRelativeTileAt(const Vector2D& relativePosition) const{
		/** BUG: this code should be relative to a topleft */
		return _grid->GetTileAt(relativePosition);
	}


}