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
	std::vector<Move>* Board::GetLegalMoves(Players player) {
		std::vector<Tile<int>>* CheckMoves = this->GetOccupiedTiles();
		std::vector<Tile<int>> resultsortof = std::vector<Tile<int>>();
		std::vector<Tile<int>> possiblity = std::vector<Tile<int>>();

		vector<Tile<int>>::iterator iterPos = CheckMoves->begin();
		while(iterPos != CheckMoves->end())
		{
			int data = *(*iterPos).GetData();
			if(player == Max)
			{
				if (data & IsMax)
				{
					resultsortof.push_back(*iterPos);
				}
			}else
			{
				if (!(data & IsMax))
				{
					resultsortof.push_back(*iterPos);
				}

			}
			iterPos++;
		}

		vector<Tile<int>>::iterator iterPos2 = resultsortof.begin();
		while(iterPos != resultsortof.end())
		{
			if(player == Max)
			{
				int checkRight = *(*iterPos2).GetRight; 
				int checkLeft = *(*iterPos2).GetLeft;
				if(!( checkRight & IsEmpty))
				{
					int jumpRight = *(*iterPos2).GetRight.GetRight;
					if(jumpRight & IsMax)
						possiblity.push_back(*(*iterPos2).GetRight.GetRight);
				}
				else
					possiblity.push_back(*(*iterPos2).GetRight);

				if(!( checkLeft& IsEmpty))
				{
					int jumpLeft = *(*iterPos2).GetLeft.GetLeft;
					if(jumpLeft & IsMax)
						possiblity.push_back(*(*iterPos2).GetLeft.GetLeft);
				}
				else
					possiblity.push_back((*iterPos2).GetLeft);

				iterPos2++;
			}
		}










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
		std::stringstream result;
		_grid->TraverseTiles(
			[&, this](Tile<int>* tile) -> void{
				int data = *tile->GetData();
				result << *tile->GetData() << ",";
				if(tile->GetPosition()->X() +1 == this->_grid->GetSize()->GetWidth()){
					result << std::endl;
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


}