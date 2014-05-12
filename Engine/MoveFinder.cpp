#include "MoveFinder.h"

namespace engine {
	MoveFinder::MoveFinder(IBoard* board) {
		_board = board;
	}

	MoveFinder::~MoveFinder(void) {
	}

	// Returns all legal moves for the current state of this._board.
	std::vector<Move>* MoveFinder::GetLegalMoves(Players player) {
		if (_board->GetPieceCountFor(player) < IBoard::MaxPiecesPerPlayer) {
			return GetLegalPlaceMoves(player);
		}
		else {
			return GetLegalMoveMoves(player);
		}
	}

	// Returns all place moves for the specified player.
	std::vector<Move>* MoveFinder::GetLegalPlaceMoves(Players player) {
		std::vector<Move>* moves = new std::vector<Move>();
		std::vector<RelativeCell>* emptyTiles = _board->GetEmptyTiles();
		for (auto it = emptyTiles->begin(); it != emptyTiles->end(); ++it) {
			// Add insertion move to an empty tile.
			moves->push_back(Move(INSERT, it->GetRelativePosition()));
		}
		return moves;
	}

	// Returns all moves that are either a jump or move type of move.
	std::vector<Move>* MoveFinder::GetLegalMoveMoves(Players player) {
		std::vector<Move>* moves = new std::vector<Move>();
		std::vector<RelativeCell>* occupiedCells = _board->GetOccupiedTiles();

		// Loop through all occupied cells.
		for (auto it = occupiedCells->begin(); it != occupiedCells->end(); ++it) {

			// If this cells contain a piece owned by player, continue.
			if ((player == Max && ((it->GetData()) & IsMax) == IsMax) ||
				(player == Min && ((it->GetData()) & IsMax) != IsMax))
			{
				AddJumpMovesToVector(*moves, *it);
				AddAdjacentMovesToVector(*moves, *it);
			}
		}
		return moves;
	}

	// Adds all possible jump moves to the specified vector.
	void MoveFinder::AddJumpMovesToVector(std::vector<Move>& moves, const RelativeCell& source) {
		if ((source.GetLeft().GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetLeft().GetLeft(),
				JUMP
			);
		}
		if ((source.GetRight().GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetRight().GetRight(),
				JUMP
			);
		}
		if ((source.GetTop().GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetTop().GetTop(),
				JUMP
			);
		}
		if ((source.GetBottom().GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetBottom().GetBottom(),
				JUMP
			);
		}

		// Diagonal
		if ((source.GetTop().GetLeft().GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetTop().GetTop().GetLeft().GetLeft(),
				JUMP
			);
		}
		if ((source.GetTop().GetRight().GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetTop().GetTop().GetRight().GetRight(),
				JUMP
			);
		}
		if ((source.GetBottom().GetLeft().GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves,
				source,
				source.GetBottom().GetBottom().GetLeft().GetLeft(),
				JUMP
			);
		}
		if ((source.GetBottom().GetRight().GetData() & (HasTile | IsEmpty)) == HasTile) {
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
		if (((to.GetData()) & (IsEmpty | HasTile)) == (IsEmpty | HasTile)) {
			moves.push_back(Move(type, (from.GetRelativePosition()), (to.GetRelativePosition())));
		}
		// If there is no tile, we have to pick a tile to move to it.
		else if (((to.GetData()) & HasTile) == 0 && _board->CountNonDiagonalEdges(to) > 0) {
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
			Vector2D diff = to.GetRelativePosition() - it->GetRelativePosition();
			if (abs((int)diff.X()) == 1 && abs((int)diff.Y()) == 1 &&
					_board->CountNonDiagonalEdges(from) <= 1) {
				continue;
			}
			moves.push_back(Move(
				type,
				from.GetRelativePosition(),
				to.GetRelativePosition(),
				it->GetRelativePosition()
			));
		}
	}
}
