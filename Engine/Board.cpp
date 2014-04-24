#include "Board.h"

namespace engine{

	const Size Board::initSize(5,4);
	Board::Board() {
		_moveFinder = new MoveFinder(this);
		_grid = new Grid<int>();
		_grid->BindCellsToEachother(true);
		_grid->TraverseCells(
			[](Cell<int>* tile) -> void{
				int* data = new int(0);
				if (tile->GetPosition().X() < Board::initSize.GetWidth() && 
					tile->GetPosition().Y() < Board::initSize.GetHeight()){
					*data |= HasCell | IsEmpty;
				} 
				tile->SetData(data);
			}
		);
		absoluteTopLeft = _grid->GetCellAt(Vector2D(0,0))->GetPosition();
	}
	Board::~Board(){
		delete _moveFinder;
		_moveFinder = nullptr;
		delete _grid;
		_grid = nullptr;
	}

	int Board::GetPieceCountFor(Players player) {
		// TODO: Actual counting.
		return 0;
	}

	void Board::ExecuteMove(Move *move, Players player) {
		switch(move->GetMoveType()){
			case INSERT:
				InsertPiece(*_grid->GetCellAt(move->GetToCell()), player);
			return;
			case DELETE:
				DeletePiece(*_grid->GetCellAt(move->GetToCell()));
			return;
			case MOVE:
				if(move->HasUsedCell()){
					MovePiece(
						*_grid->GetCellAt(move->GetFromCell()), 
						*_grid->GetCellAt(move->GetToCell()), 
						player, 
						*_grid->GetCellAt(move->GetUsedCell()) 
					);
					return;
				}
				MovePiece(
					*_grid->GetCellAt(move->GetFromCell()), 
					*_grid->GetCellAt(move->GetToCell()), 
					player
				);
			return; 
			case JUMP:
				if(move->HasUsedCell()){
					JumpPiece(
						*_grid->GetCellAt(move->GetFromCell()), 
						*_grid->GetCellAt(move->GetToCell()), 
						player, 
						*_grid->GetCellAt(move->GetUsedCell()) 
					);
					return;
				}
				JumpPiece(
					*_grid->GetCellAt(move->GetFromCell()), 
					*_grid->GetCellAt(move->GetToCell()), 
					player
				);
			return; 
		}
		
	}

	void Board::InsertPiece(Cell<int>& on, Players owner){
		on.SetData(on.GetData() & ~IsEmpty);
		if(owner == Max) {
			on.SetData(on.GetData() | IsMax);
			return;
		}
		on.SetData(on.GetData() & ~IsMax);
	}
	void Board::DeletePiece(Cell<int>& on){
		on.SetData(on.GetData() | IsEmpty);
	}
	void Board::MovePiece(Cell<int>& from, Cell<int>& to, Players owner, Cell<int>& tileUsed){
		tileUsed.SetData(tileUsed.GetData() & ~HasCell);
		tileUsed.SetData(to.GetData() | HasCell);
		MovePiece(from, to, owner);
	}
	void Board::MovePiece(const Cell<int>& from, const Cell<int>& to, Players owner){

		*to.GetData() = *from.GetData();
		DeletePiece(from);
	}
	void Board::JumpPiece(const Cell<int>& from, const Cell<int>& to, Players owner, const Cell<int>& tileUsed){
		MovePiece(from, to, owner, tileUsed);
	}
	void Board::JumpPiece(const Cell<int>& from, const Cell<int>& to, Players owner){
		MovePiece(from, to, owner);
	}


	vector<Move>* Board::GetLegalMoves(Players player) {
		return _moveFinder->GetLegalMoves(player);
	}

	vector<Cell<int>>* Board::GetOccupiedCells(){
		auto tiles = new vector<Cell<int>>();
		_grid->TraverseCells(
			[&](Cell<int>* tile) -> void{
				if(!*tile->GetData() & HasCell){
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

	vector<Cell<int>>* Board::GetEmptyTiles() {
		vector<Cell<int>>* emptyTiles = new vector<Cell<int>>();
		_grid->TraverseCells(
			[&](Cell<int>* tile) -> void{
				// Stop if cell does not contain a tile.
				if(!*tile->GetData() & HasCell){
					return;
				}
				// Stop if tile is not empty.
				if((*tile->GetData() & IsEmpty) == 0){
					return;
				}
				emptyTiles->push_back(*tile);
			}
		);
		return emptyTiles;
	}

	string Board::ToString(){
		stringstream result;
		_grid->TraverseCells(
			[&, this](Cell<int>* tile) -> void{
				int data = *tile->GetData();
				result << *tile->GetData() << ",";
				if(tile->GetPosition().X() +1 == this->_grid->GetSize()->GetWidth()){
					result << endl;
				}
			}
		);
		return result.str();
		
	}
	Cell<int>* Board::GetRelativeCellAt(const Vector2D relativePosition) const{
		Vector2D position = relativePosition + absoluteTopLeft;
		if(position.X() < 0){
			position.X(position.X() + _grid->GetSize()->GetWidth());
		}
		if(position.Y() < 0){
			position.Y(position.Y() + _grid->GetSize()->GetWidth());
		}
		return _grid->GetCellAt(position);
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
			Cell<int>* cell = result->_grid->GetCellAt(Vector2D(x, y));
			cell->SetData(subject - '0');
		}
		int pause = 0;
		return result;
	}

}
