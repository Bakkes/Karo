#include "Board.h"
namespace engine{

	const Size Board::initSize(5,4);
	Board::Board(){
		_grid = new Grid<int>();
		_grid->BindTilesToEachother(true);
		_grid->TraverseTiles(
			[](Tile<int>* tile) -> void{
				int* data = new int(0);
				if( tile->GetPosition()->X() < Board::initSize.GetWidth() && 
					tile->GetPosition()->Y() < Board::initSize.GetHeight()){
					*data |= HasTile | IsEmpty;
				} 
				tile->SetData(data);
			}
		);
		absoluteTopLeft = *_grid->GetTileAt(Vector2D(0,0))->GetPosition();
	}
	Board::~Board(){
		delete _grid;
	}

	void Board::ExecuteMove(Move *move, Players player) {
		switch(move->GetMoveType()){
			case INSERT:
				InsertPiece(*_grid->GetTileAt(move->GetToTile()), player);
			return;
			case DELETE:
				DeletePiece(*_grid->GetTileAt(move->GetToTile()));
			return;
			case MOVE:
				if(move->HasUsedTile()){
					MovePiece(
						*_grid->GetTileAt(move->GetFromTile()), 
						*_grid->GetTileAt(move->GetToTile()), 
						player, 
						*_grid->GetTileAt(move->GetUsedTile()) 
					);
					return;
				}
				MovePiece(
					*_grid->GetTileAt(move->GetFromTile()), 
					*_grid->GetTileAt(move->GetToTile()), 
					player
				);
			return; 
			case JUMP:
				if(move->HasUsedTile()){
					JumpPiece(
						*_grid->GetTileAt(move->GetFromTile()), 
						*_grid->GetTileAt(move->GetToTile()), 
						player, 
						*_grid->GetTileAt(move->GetUsedTile()) 
					);
					return;
				}
				JumpPiece(
					*_grid->GetTileAt(move->GetFromTile()), 
					*_grid->GetTileAt(move->GetToTile()), 
					player
				);
			return; 
		}
		
	}

	void Board::InsertPiece(const Tile<int>& on, Players owner){
		*on.GetData() &= ~IsEmpty;
		if(owner == Max){
			*on.GetData() |= IsMax;
			return;
		}
		*on.GetData() &= ~IsMax;
	}
	void Board::DeletePiece(const Tile<int>& on){
		*on.GetData() |= IsEmpty;
	}
	void Board::MovePiece(const Tile<int>& from, const Tile<int>& to, Players owner, const Tile<int>& tileUsed){
		*tileUsed.GetData() &= ~HasTile;
		*to.GetData() |= HasTile;
		MovePiece(from, to, owner);
	}
	void Board::MovePiece(const Tile<int>& from, const Tile<int>& to, Players owner){
		*to.GetData() = *from.GetData();
		DeletePiece(from);
	}
	void Board::JumpPiece(const Tile<int>& from, const Tile<int>& to, Players owner, const Tile<int>& tileUsed){
		MovePiece(from, to, owner, tileUsed);
	}
	void Board::JumpPiece(const Tile<int>& from, const Tile<int>& to, Players owner){
		MovePiece(from, to, owner);
	}
	vector<Move>* Board::GetLegalMoves(Players player) {
		return new vector<Move>();
	}
	vector<Tile<int>>* Board::GetOccupiedTiles(){
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
	string Board::ToString(){
		stringstream result;
		_grid->TraverseTiles(
			[&, this](Tile<int>* tile) -> void{
				int data = *tile->GetData();
				result << *tile->GetData() << ",";
				if(tile->GetPosition()->X() +1 == this->_grid->GetSize()->GetWidth()){
					result << endl;
				}
			}
		);
		return result.str();
		
	}
	Tile<int>* Board::GetRelativeTileAt(const Vector2D relativePosition) const{
		Vector2D position = relativePosition + absoluteTopLeft;
		if(position.X() < 0){
			position.X(position.X() + _grid->GetSize()->GetWidth());
		}
		if(position.Y() < 0){
			position.Y(position.Y() + _grid->GetSize()->GetWidth());
		}
		return _grid->GetTileAt(position);
	}

	Board* Board::CreateBoard(string from){
		Board* result = new Board();
		int y = 0, x = 0;
		for (
			string::iterator it = from.begin();
			it < from.end();
			it++ ,x++
		){
			char subject = *it;
			if(subject == ','){
				x--;
				continue;
			}
			if(subject == '\n'){
				y++;
				x = 0;
				continue;
			}
			*result->_grid->GetTileAt(Vector2D(x,y))->GetData() = subject -'0';
		}
		int pause = 0;
		return result;
	}

}