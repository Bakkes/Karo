#include "MoveFinder.h"

namespace engine {
	MoveFinder::MoveFinder(Board* board) {
		_board = board;
		_checkedCells = new std::vector<const RelativeCell>();
	}

	MoveFinder::~MoveFinder(void) {
		delete _checkedCells;
		_checkedCells = nullptr;
	}

	// Returns all legal moves for the current state of this._board.
	std::vector<Move> MoveFinder::GetLegalMoves(Players player) {
		if (_board->GetPieceCountFor(player) < IBoard::MaxPiecesPerPlayer) {
			return GetLegalPlaceMoves(player);
		}
		else {
			return GetLegalMoveMoves(player);
		}
	}

	// Returns all place moves for the specified player.
	std::vector<Move> MoveFinder::GetLegalPlaceMoves(Players player) {
	
		std::vector<Move> moves = std::vector<Move>();
		std::vector<RelativeCell>* emptyTiles = _board->GetEmptyTiles();
		for (auto it = emptyTiles->begin(); it != emptyTiles->end(); ++it) {
			// Add insertion move to an empty tile.
			moves.push_back(Move(INSERT, Vector2D(), it->GetRelativePosition()));
		} 
		return moves;
	}

	// Returns all moves that are either a jump or move type of move.
	std::vector<Move> MoveFinder::GetLegalMoveMoves(Players player) {
		std::vector<Move> moves = std::vector<Move>();
		std::vector<RelativeCell>* occupiedCells = _board->GetOccupiedTiles();

		// Loop through all occupied cells.
		for (auto it = occupiedCells->begin(); it != occupiedCells->end(); ++it) {

			// If this cells contain a piece owned by player, continue.
			if ((player == Max && it->IsMaxPiece()) ||
				(player == Min && !it->IsMaxPiece()))
			{
				AddJumpMovesToVector(moves, *it);
				AddAdjacentMovesToVector(moves, *it);
			}
		}
		return moves;
	}

	// Adds all possible jump moves to the specified vector.
	void MoveFinder::AddJumpMovesToVector(std::vector<Move>& moves, const RelativeCell& source) {
		if (CellHasTileWithPlayer(source.GetLeft())) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetLeft().GetLeft(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetRight())) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetRight().GetRight(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetTop())) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetTop().GetTop(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetBottom())) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetBottom().GetBottom(),
				JUMP
			);
		}

		// Diagonal
		if (CellHasTileWithPlayer(source.GetTop().GetLeft())) { 
			AddMoveIfValidDestination(moves,
				source,
				source.GetTop().GetTop().GetLeft().GetLeft(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetTop().GetRight())) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetTop().GetTop().GetRight().GetRight(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetBottom().GetLeft())) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetBottom().GetBottom().GetLeft().GetLeft(),
				JUMP
			);
		}
		if (CellHasTileWithPlayer(source.GetBottom().GetRight())) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetBottom().GetBottom().GetRight().GetRight(),
				JUMP
			);
		}
	}

	// Adds all adjecent move options to the specified move vector.
	void MoveFinder::AddAdjacentMovesToVector(std::vector<Move>& moves, const RelativeCell& cell) {
		AddMoveIfValidDestination(moves, cell, cell.GetLeft(), STEP);
		AddMoveIfValidDestination(moves, cell, cell.GetRight(), STEP);
		AddMoveIfValidDestination(moves, cell, cell.GetTop(), STEP);
		AddMoveIfValidDestination(moves, cell, cell.GetBottom(), STEP);

		// Diagonal
		AddMoveIfValidDestination(moves, cell, cell.GetTop().GetLeft(), STEP);
		AddMoveIfValidDestination(moves, cell, cell.GetTop().GetRight(), STEP);
		AddMoveIfValidDestination(moves, cell, cell.GetBottom().GetLeft(), STEP);
		AddMoveIfValidDestination(moves, cell, cell.GetBottom().GetRight(), STEP);
	}

	// Assumes that the fromtile has a piece on it.
	void MoveFinder::AddMoveIfValidDestination(
		std::vector<Move>& moves,
		const RelativeCell &from,
		const RelativeCell &to,
		const MoveType& type)
	{
		// If there is a tile and it is empty, we can move the piece to it.
		if (to.IsEmpty() && to.HasTile()) {
			moves.push_back(Move(type, from.GetRelativePosition(), to.GetRelativePosition()));
		}
		// If there is no tile, we have to pick a tile to move to it.
		else if ((!to.HasTile()) && (_board->CountNonDiagonalEdges(to) > 0)) {
			AddTileMoveMoves(moves, type, from, to);
		}
	}

	// Adds all moves that move an empty tile for the specified source/destination.
	void MoveFinder::AddTileMoveMoves(
		std::vector<Move>& moves,
		const MoveType& type,
		const RelativeCell& from,
		const RelativeCell& to) {
		std::vector<RelativeCell>* emptyCells = _board->GetEmptyTiles();
		for (auto it = emptyCells->begin(); it != emptyCells->end(); ++it) {
			if (_board->CountNonDiagonalEdges(*it) > 2) {
				continue;
			}
			// Rule amendment solution
			// - From tile has 0 or 1 edges
			// - to and used tile are diagonal (relative to eachother)
			// then this move is illegal
			Vector2D diff = to.GetRelativePosition() - it->GetRelativePosition();
			if (abs((int)diff.X()) == 1 && abs((int)diff.Y()) == 1 &&
					_board->CountNonDiagonalEdges(from) <= 1) {
				continue;
			}
			// Create potential move.
			Move move(type,
				from.GetRelativePosition(),
				to.GetRelativePosition(),
				it->GetRelativePosition()
			);
			_board->ExecuteMove(move, from.GetPlayer());
			if (ConnectedTiles(from) != 20) {
				// An island was created, stop!
				_board->UndoMove(move, from.GetPlayer());
				continue;
			}
			_board->UndoMove(move, from.GetPlayer());
			moves.push_back(move);
		}
	}

	int MoveFinder::ConnectedTiles(const RelativeCell &start) {
		_checkedCells->clear();
		return ConnectedTilesRecursive(start);
	}

	int MoveFinder::ConnectedTilesRecursive(const RelativeCell &start) {
		string boardString = _board->ToString();
		for (auto it = _checkedCells->begin(); it != _checkedCells->end(); ++it) {
			if (start == *it) {
				return 0;
			}
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
