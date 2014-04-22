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


	std::vector<Move> Board::FindMove(Tile<int> one,Tile<int> two)
	{
		std::vector<Move> possibility = std::vector<Move>();

		int checkRight = *one.GetData(); 

		if(!( checkRight & IsEmpty))
		{
			int jumpRight = *two.GetData();
			if(jumpRight & IsEmpty)
			{
				if(jumpRight & HasTile)
					possibility.push_back(Move(JUMP,*two.GetPosition()));
				else 
					ForPickableTiles([&](Tile<int>* tile) -> void{
						possibility.push_back(*tile);
				});
			}
		}
		else {
			possibility.push_back(Move(MOVE,*one.GetPosition()));
		}

		return possibility;
	}


	std::vector<Move> Board::GetLegalMoves(Tile<int> iterPos2, Players Player ) 
	{
		std::vector<Move> possibility = std::vector<Move>();
	

		if(Player == Max)
			{
				std::vector<Move> possibility2 = FindMove(*iterPos2.GetRight(),*iterPos2.GetRight()->GetRight());
				possibility.insert(possibility.end(),possibility2.begin(),possibility2.end());

				possibility2 = FindMove(*iterPos2.GetLeft(),*iterPos2.GetLeft()->GetLeft());
				possibility.insert(possibility.end(),possibility2.begin(),possibility2.end());

				possibility2 = FindMove(*iterPos2.GetTop(),*iterPos2.GetTop()->GetTop());
				possibility.insert(possibility.end(),possibility2.begin(),possibility2.end());

				possibility2 = FindMove(*iterPos2.GetBottom(),*iterPos2.GetBottom()->GetBottom());
				possibility.insert(possibility.end(),possibility2.begin(),possibility2.end());

				possibility2 = FindMove(*iterPos2.GetBottomLeft(),*iterPos2.GetBottomLeft()->GetBottomLeft());
				possibility.insert(possibility.end(),possibility2.begin(),possibility2.end());

				possibility2 = FindMove(*iterPos2.GetBottomRight(),*iterPos2.GetBottomRight()->GetBottomRight());
				possibility.insert(possibility.end(),possibility2.begin(),possibility2.end());

				possibility2 = FindMove(*iterPos2.GetTopLeft(),*iterPos2.GetTopLeft()->GetTopLeft());
				possibility.insert(possibility.end(),possibility2.begin(),possibility2.end());

				possibility2 = FindMove(*iterPos2.GetTopRight(),*iterPos2.GetTopRight()->GetTopRight());
				possibility.insert(possibility.end(),possibility2.begin(),possibility2.end());



				
			} 
		return possibility;
	}

	void Board::ForPickableTiles(function< void(Tile<int>*) >& lambda)
	{
		

		_grid->TraverseTiles(
			[&](Tile<int>* tile) -> void{
				if(!(*tile->GetData() & IsEmpty)) 
				{
					return;
				}
				if(!HasTile & *tile->GetData())
				{
					return;
				}
				int attatchCount =0;
				if(*tile->GetLeft()->GetData() & HasTile)
				{
					attatchCount ++;
				}
				
				if(*tile->GetRight() ->GetData() & HasTile)
				{
					attatchCount++;
				}
				
				if(*tile->GetRight() ->GetData() & HasTile)
				{
					attatchCount++;
				}
				
				if(*tile->GetRight() ->GetData() & HasTile)
				{
					attatchCount++;
				}

				if(attatchCount <=2)
					lambda(tile);
			}
		);
		

	}
	std::vector<Move>* Board::GetLegalMoves(Players player) {
		std::vector<Tile<int>>* CheckMoves = this->GetOccupiedTiles();
		std::vector<Tile<int>> resultsortof = std::vector<Tile<int>>();
		std::vector<Move> *possibility = new std::vector<Move>();
	
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
		while(iterPos2 != resultsortof.end())
		{
			std::vector<Move> possibility2 = GetLegalMoves(*iterPos2,player);
			possibility->insert(possibility->end(),possibility2.begin(),possibility2.end());
			iterPos2++;
		}

		return possibility;
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