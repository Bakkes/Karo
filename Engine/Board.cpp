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
						data |= HasTile | IsEmpty;
					}
					tile->SetData(data);
				}
			);
			_converter = new RelativeAbsoluteConverter(_grid);
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
		delete _converter;
		_converter = NULL;
	}

	int Board::GetPieceCountFor(Players player) {

		int playerCount = 0;
		int isMax = player == Max ? IsMax : 0;

		// Traverse the board and count all players.
		_grid->TraverseCells(
			[&](Cell<int>* tile) -> void {
				int data = tile->GetData();
				if ((data & HasTile) && (data & IsEmpty) == 0) {
					if ((data & IsMax) == isMax) {
						playerCount++;
					}
				}
			}
		);
		return playerCount;
	}

	void Board::ExecuteMove(Move *move, Players player) {
		Vector2D from = _converter->ToAbsolute(move->GetFromCell());
		Vector2D to = _converter->ToAbsolute(move->GetToCell());
		Vector2D used;
		if(move->HasUsedCell()){
			used = _converter->ToAbsolute(move->GetUsedCell());
		}
		switch(move->GetMoveType()){
			case INSERT:
				InsertPiece(*_grid->GetCellAt(to), player);
			return;
			case DELETE:
				DeletePiece(*_grid->GetCellAt(to));
			return;
			case STEP:
				if(move->HasUsedCell()){
					MovePiece(
						*_grid->GetCellAt(from), 
						*_grid->GetCellAt(to), 
						player, 
						*_grid->GetCellAt(used) 
					);
					return;
				}
				MovePiece(
					*_grid->GetCellAt(from), 
					*_grid->GetCellAt(to), 
					player
				);
			return; 
			case JUMP:
				if(move->HasUsedCell()){
					JumpPiece(
						*_grid->GetCellAt(from), 
						*_grid->GetCellAt(to), 
						player, 
						*_grid->GetCellAt(used) 
					);
					return;
				}
				JumpPiece(
					*_grid->GetCellAt(from), 
					*_grid->GetCellAt(to), 
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
		_converter->MoveTile(tileUsed.GetPosition(), to.GetPosition());
		tileUsed.SetData(tileUsed.GetData() & ~HasTile);
		to.SetData(to.GetData() | HasTile);
		MovePiece(from, to, owner);
	}
	void Board::MovePiece(Cell<int>& from, Cell<int>& to, Players owner){

		to.SetData(from.GetData());
		DeletePiece(from);
	}
	void Board::JumpPiece(Cell<int>& from, Cell<int>& to, Players owner, Cell<int>& tileUsed){
		Flip(from);
		MovePiece(from, to, owner, tileUsed);
	}
	void Board::JumpPiece(Cell<int>& from, Cell<int>& to, Players owner){
		Flip(from);
		MovePiece(from, to, owner);
	}
	void Board::Flip(Cell<int>& which){
		which.SetData(which.GetData() ^ IsFlipped);
	}


	vector<Move> Board::GetLegalMoves(Players player) {
		return _moveFinder->GetLegalMoves(player);
	}

	vector<RelativeCell>* Board::GetOccupiedTiles(){
		auto tiles = new vector<RelativeCell>();
		_grid->TraverseCells(
			[&](Cell<int>* tile) -> void{
				if(!tile->GetData() & HasTile){
					return;
				}
				if(tile->GetData() & IsEmpty){
					return;
				}
				tiles->push_back(RelativeCell(tile, _converter));
			}
		);
		return tiles;
	}

	vector<RelativeCell>* Board::GetEmptyTiles() {
		vector<RelativeCell>* emptyTiles = new vector<RelativeCell>();
		_grid->TraverseCells(
			[&](Cell<int>* tile) -> void{
				if (tile->GetData() == 2)
					int i = 5;
				// Stop if cell does not contain a tile.
				if(!(tile->GetData() & HasTile)){
					return;
				}
				// Stop if tile is not empty.
				if((tile->GetData() & IsEmpty) == 0){
					return;
				}
				emptyTiles->push_back(RelativeCell(tile, _converter));
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
	RelativeCell Board::GetRelativeCellAt(const Vector2D& relativePosition) const{
		return RelativeCell(
			_grid->GetCellAt(_converter->ToAbsolute(relativePosition)),
			_converter
		);
	}


	Cell<int>* Board::GetAbsoluteCellAt(const Vector2D absolutePosition) const{

		return _grid->GetCellAt(absolutePosition);
	}


	Board* Board::CreateBoard(string from) {
		return Board::CreateBoard(from, Vector2D(0));
	}
	Board* Board::CreateBoard(string from, Vector2D absoluteTopLeft) {
		Board* result = new Board(false);
		int y = 0, x = 0;
		for (string::iterator it = from.begin(); it < from.end(); it++) {
			char subject = *it;
			int myWonderfulNumber = 0;
			bool inWhile = false;

			while(subject >= '0' && subject <= '9') {
				myWonderfulNumber *= 10;
				myWonderfulNumber += subject - '0';
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
			result->_grid->GetCellAt(Vector2D(x,y))->SetData(myWonderfulNumber);
		}

		result->_converter = new RelativeAbsoluteConverter(result->_grid,absoluteTopLeft);
		return result;
	}
	int Board::CountNonDiagonalEdges(const RelativeCell& cell) {
		int edges = 0;
		
		if (cell.GetLeft().HasTile()) {
			edges++;
		}
		if (cell.GetRight().HasTile()) {
			edges++;
		}
		if (cell.GetTop().HasTile()) {
			edges++;
		}
		if (cell.GetBottom().HasTile()) {
			edges++;
		}

		return edges;
	}
}
