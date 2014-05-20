#include "MoveFinder.h"

namespace engine {
	MoveFinder::MoveFinder(Board* board) {
		_board = board;
		Invalidate();
		_cachedMoves = new std::vector<Move>();
		_checkedCells = new std::vector<const RelativeCell>();
	}

	MoveFinder::~MoveFinder(void) {
		delete _checkedCells;
		_checkedCells = nullptr;
		delete _cachedMoves;
		_cachedMoves = nullptr;
	}

	void MoveFinder::Invalidate() {
		this->_invalidatedMax = true;
		this->_invalidatedMin = true;
	}

	// Returns all legal moves for the current state of this._board.
	std::vector<Move> MoveFinder::GetLegalMoves(Players player) {
		if (player == Max && !_invalidatedMax ||
			player == Min && !_invalidatedMin) {
			// Return cached moves if not invalidated.
			return (*_cachedMoves);
		}
		// Enable caching.
		if (player == Max) { _invalidatedMax = false; }
		if (player == Min) { _invalidatedMin = false; }
		_cachedMoves->clear();
		delete _cachedMoves;
		_cachedMoves = new vector<Move>();
		if (_board->GetPieceCountFor(player) < IBoard::MaxPiecesPerPlayer) {
			return (*GetLegalPlaceMoves(player));
		}
		else {
			return (*GetLegalMoveMoves(player));
		}
	}

	// Returns all place moves for the specified player.
	std::vector<Move>* MoveFinder::GetLegalPlaceMoves(Players player) {
		std::vector<RelativeCell>* emptyTiles = _board->GetEmptyTiles();
		for_each(emptyTiles->begin(), emptyTiles->end(), [this](RelativeCell& cell) -> void{
			_cachedMoves->push_back(Move(INSERT, Vector2D(), cell.GetRelativePosition()));	
		});
		return _cachedMoves;
	}

	// Returns all moves that are either a jump or move type of move.
	std::vector<Move>* MoveFinder::GetLegalMoveMoves(Players player) {
		std::vector<RelativeCell> occupiedCells = std::vector<RelativeCell>(*_board->GetOccupiedTiles());

		for_each(occupiedCells.begin(), occupiedCells.end(), [&,this](RelativeCell& cell) -> void{
			// If this cells contain a piece owned by player, continue.
			if ((player == Max && cell.IsMaxPiece()) ||
				(player == Min && !cell.IsMaxPiece()))
			{
				AddJumpMovesToVector(cell);
				AddAdjacentMovesToVector(cell);
			}
		});
		return _cachedMoves;
	}

	// Adds all possible jump moves to the specified vector.
	void MoveFinder::AddJumpMovesToVector(const RelativeCell& source) {
		if (CellHasTileWithPlayer(source.GetLeft())) {
			AddMoveIfValidDestination(
				source,
				source.GetLeft().GetLeft(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetRight())) {
			AddMoveIfValidDestination(
				source,
				source.GetRight().GetRight(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetTop())) {
			AddMoveIfValidDestination(
				source,
				source.GetTop().GetTop(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetBottom())) {
			AddMoveIfValidDestination(
				source,
				source.GetBottom().GetBottom(),
				JUMP
			);
		}

		// Diagonal
		if (CellHasTileWithPlayer(source.GetTop().GetLeft())) { 
			AddMoveIfValidDestination(
				source,
				source.GetTop().GetTop().GetLeft().GetLeft(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetTop().GetRight())) {
			AddMoveIfValidDestination(
				source,
				source.GetTop().GetTop().GetRight().GetRight(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetBottom().GetLeft())) {
			AddMoveIfValidDestination(
				source,
				source.GetBottom().GetBottom().GetLeft().GetLeft(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetBottom().GetRight())) {
			AddMoveIfValidDestination(
				source,
				source.GetBottom().GetBottom().GetRight().GetRight(),
				JUMP
			);
		}
	}

	// Adds all adjecent move options to the specified move vector.
	void MoveFinder::AddAdjacentMovesToVector(const RelativeCell& cell) {
		AddMoveIfValidDestination(cell, cell.GetLeft(), STEP);
		AddMoveIfValidDestination(cell, cell.GetRight(), STEP);
		AddMoveIfValidDestination(cell, cell.GetTop(), STEP);
		AddMoveIfValidDestination(cell, cell.GetBottom(), STEP);

		// Diagonal
		AddMoveIfValidDestination(cell, cell.GetTop().GetLeft(), STEP);
		AddMoveIfValidDestination(cell, cell.GetTop().GetRight(), STEP);
		AddMoveIfValidDestination(cell, cell.GetBottom().GetLeft(), STEP);
		AddMoveIfValidDestination(cell, cell.GetBottom().GetRight(), STEP);
	}

	// Assumes that the fromtile has a piece on it.
	void MoveFinder::AddMoveIfValidDestination(
		const RelativeCell &from,
		const RelativeCell &to,
		const MoveType& type)
	{
		// If there is a tile and it is empty, we can move the piece to it.
		if (to.IsEmpty() && to.HasTile()) {
			_cachedMoves->push_back(Move(type, from.GetRelativePosition(), to.GetRelativePosition()));
		}
		// If there is no tile, we have to pick a tile to move to it.
		else if ((!to.HasTile()) && (_board->CountNonDiagonalEdges(to) > 0)) {
			AddTileMoveMoves(type, from, to);
		}
	}

	// Adds all moves that move an empty tile for the specified source/destination.
	void MoveFinder::AddTileMoveMoves(
		const MoveType& type,
		const RelativeCell& from,
		const RelativeCell& to) {
		std::vector<RelativeCell> emptyCells = std::vector<RelativeCell>(*_board->GetEmptyTiles());
		for_each(emptyCells.begin(), emptyCells.end(), [&,this](RelativeCell& cell) -> void{
			if (_board->CountNonDiagonalEdges(cell) > 2) {
				return;// continue does not work return is the same
			}
			// Rule amendment solution
			// - From tile has 0 or 1 edges
			// - to and used tile are diagonal (relative to eachother)
			// then this move is illegal
			Vector2D diff = to.GetRelativePosition() - cell.GetRelativePosition();
			if (abs((int)diff.X()) <= 1 && abs((int)diff.Y()) <= 1) {
				_board->DeleteTileAt(cell.GetRelativePosition());
				int connectedTiles = ConnectedTiles(from);
				_board->CreateTileAt(cell.GetRelativePosition());
				if (connectedTiles != 19) {
					return;
				}
			}
			// Create potential move.
			Move move(type,
				from.GetRelativePosition(),
				to.GetRelativePosition(),
				cell.GetRelativePosition()
			);
			Players player = from.GetPlayer();
			_board->ExecuteMove(move, player);
			if (ConnectedTiles(from) != 20) {
				// An island was created, stop!
				_board->UndoMove(move, player);
				return;
			}
			_board->UndoMove(move, player);
			_cachedMoves->push_back(move);
		});
		// This is to prevent the UndoMove and ExecuteMove in this method
		// from invalidating the cache.
		if (from.GetPlayer() == Max) { _invalidatedMax = false; }
		if (from.GetPlayer() == Min) { _invalidatedMin = false; }
	}

	int MoveFinder::ConnectedTiles(const RelativeCell &start) {
		_checkedCells->clear();
		delete _checkedCells;
		_checkedCells = new vector<const RelativeCell>();
		return ConnectedTilesRecursive(start);
	}

	int MoveFinder::ConnectedTilesRecursive(const RelativeCell &start) {
		for(unsigned i = 0; i < _checkedCells->size(); i++) {
			if(_checkedCells->at(i) == start)
				return 0;
		}
		_checkedCells->push_back(start);
		int result = 1;
		if (start.GetLeft().HasTile()) {
			result += ConnectedTilesRecursive(start.GetLeft());
		}
		if (start.GetRight().HasTile()) {
			result += ConnectedTilesRecursive(start.GetRight());
		}
		if (start.GetTop().HasTile()) {
			result += ConnectedTilesRecursive(start.GetTop());
		}
		if (start.GetBottom().HasTile()) {
			result += ConnectedTilesRecursive(start.GetBottom());
		}
		return result;
	}

	bool MoveFinder::CellHasTileWithPlayer(const RelativeCell &cell) {
		return cell.HasTile() && !cell.IsEmpty();
	}
}
