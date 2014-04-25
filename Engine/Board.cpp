#include "Board.h"

namespace engine{

	const Size Board::initSize(5,4);

	Board::Board(bool init) {
		Init(init);
	}

	void Board::Init(bool init) {
		_moveFinder = new MoveFinder(this);
		_grid = new Grid<int>();
		_grid->BindCellsToEachother(true);
		if(init) {
			_grid->TraverseCells(
				[](Cell<int>* tile) -> void {
					int data = 0;
					if( tile->GetPosition().X() < Board::initSize.GetWidth() &&
						tile->GetPosition().Y() < Board::initSize.GetHeight())
					{
						data |= HasCell | IsEmpty;
					}
					tile->SetData(data);
				}
			);
			_absoluteTopLeft = Vector2D(0,0);
		}
	}

	Board::Board() {
		Init(true);
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
	void Board::MovePiece(Cell<int>& from, Cell<int>& to, Players owner){

		to.SetData(from.GetData());
		DeletePiece(from);
	}
	void Board::JumpPiece(Cell<int>& from, Cell<int>& to, Players owner, Cell<int>& tileUsed){
		MovePiece(from, to, owner, tileUsed);
	}
	void Board::JumpPiece(Cell<int>& from, Cell<int>& to, Players owner){
		MovePiece(from, to, owner);
	}


	vector<Move>* Board::GetLegalMoves(Players player) {
		return _moveFinder->GetLegalMoves(player);
	}

	vector<Cell<int>>* Board::GetOccupiedTiles(){
		auto tiles = new vector<Cell<int>>();
		_grid->TraverseCells(
			[&](Cell<int>* tile) -> void{
				if(!tile->GetData() & HasCell){
					return;
				}
				if(tile->GetData() & IsEmpty){
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
				if(!tile->GetData() & HasCell){
					return;
				}
				// Stop if tile is not empty.
				if((tile->GetData() & IsEmpty) == 0){
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
				int data = tile->GetData();
				result << tile->GetData() << ",";
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

	Board* Board::CreateBoard(string from, Vector2D absoluteTopLeft) {
		Board* result = new Board(false);
		int y = 0, x = 0;
		for (string::iterator it = from.begin(); it < from.end(); it++) {
			char subject = *it;
			int myWonderfolNumber = 0;
			bool inWhile = false;

			while(subject >= '0' && subject <= '9') {
				myWonderfolNumber *= 10;
				myWonderfolNumber += subject - '0';
				it++;
				subject = *it;
				inWhile = true;
			}

			if(!inWhile) {
				if(subject == ',') {
					x++;
					continue;
				}
				if(subject == '\n') {
					y++;
					x = 0; // because one increase next cycle
					continue;
				}
			} else {
				it--;
			}
			result->_grid->GetCellAt(Vector2D(x,y))->SetData(myWonderfolNumber);
		}

		result->_absoluteTopLeft = absoluteTopLeft;
		return result;
	}

}
