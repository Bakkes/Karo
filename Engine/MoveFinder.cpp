#include "MoveFinder.h"
#include "Cell.h"

namespace engine {
	MoveFinder::MoveFinder(Board* board) {
		_board = board;
	}

	MoveFinder::~MoveFinder(void) {
	}

	std::vector<Move>* MoveFinder::GetLegalMoves(Players player) {
		if (_board->GetPieceCountFor(player) < Board::MaxPiecesPerPlayer) {
			return GetLegalPlaceMoves(player);
		}
		else {
			return GetLegalMoveMoves(player);
		}
	}

	std::vector<Move>* MoveFinder::GetLegalPlaceMoves(Players player) {
		std::vector<Move>* moves = new std::vector<Move>();
		std::vector<Cell<int>>* emptyTiles = _board->GetEmptyTiles();
		for (auto it = emptyTiles->begin(); it != emptyTiles->end(); ++it) {
			// Add insertion move to an empty tile.
			moves->push_back(Move(INSERT, Vector2D(), (*it).GetPosition()));
		}
		return moves;
	}

	std::vector<Move>* MoveFinder::GetLegalMoveMoves(Players player) {
		std::vector<Move>* moves = new std::vector<Move>();
		std::vector<Cell<int>>* occupiedCells = _board->GetOccupiedTiles();

		// Loop through all occupied cells.
		for (auto it = occupiedCells->begin(); it != occupiedCells->end(); ++it) {

			// If this cells contain a piece owned by player, continue.
			if ((player == Max && ((it->GetData()) & IsMax) == IsMax) ||
				(player == Min && ((it->GetData()) & IsMax) != IsMax))
			{
				AddJumpMovesToVector(moves, *it);
				AddAdjecentMovesToVector(moves, *it);
			}
		}
		return moves;
	}

	void MoveFinder::AddJumpMovesToVector(std::vector<Move>* moves, Cell<int> source) {
		if ((source.GetLeft()->GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves, source, *source.GetLeft()->GetLeft(), JUMP);
		}
		if ((source.GetRight()->GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves, source, *source.GetRight()->GetRight(), JUMP);
		}
		if ((source.GetTop()->GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves, source, *source.GetTop()->GetTop(), JUMP);
		}
		if ((source.GetBottom()->GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves, source, *source.GetBottom()->GetBottom(), JUMP);
		}

		// Diagonal
		if ((source.GetTop()->GetLeft()->GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves, source, *source.GetTop()->GetTop()->GetLeft()->GetLeft(), JUMP);
		}
		if ((source.GetTop()->GetRight()->GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves, source, *source.GetTop()->GetTop()->GetRight()->GetRight(), JUMP);
		}
		if ((source.GetBottom()->GetLeft()->GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves, source, *source.GetBottom()->GetBottom()->GetLeft()->GetLeft(), JUMP);
		}
		if ((source.GetBottom()->GetRight()->GetData() & (HasTile | IsEmpty)) == HasTile) {
			AddMoveIfValidDestination(moves, source, *source.GetBottom()->GetBottom()->GetRight()->GetRight(), JUMP);
		}
	}

	// Adds all adjecent move options.
	void MoveFinder::AddAdjecentMovesToVector(std::vector<Move>* moves, Cell<int> cell) {
		AddMoveIfValidDestination(moves, cell, *cell.GetLeft(), STEP);
		AddMoveIfValidDestination(moves, cell, *cell.GetRight(), STEP);
		AddMoveIfValidDestination(moves, cell, *cell.GetTop(), STEP);
		AddMoveIfValidDestination(moves, cell, *cell.GetBottom(), STEP);

		// Diagonal
		AddMoveIfValidDestination(moves, cell, *cell.GetTop()->GetLeft(), STEP);
		AddMoveIfValidDestination(moves, cell, *cell.GetTop()->GetRight(), STEP);
		AddMoveIfValidDestination(moves, cell, *cell.GetBottom()->GetLeft(), STEP);
		AddMoveIfValidDestination(moves, cell, *cell.GetBottom()->GetRight(), STEP);
	}

	// Assumes that the fromtile has a piece on it.
	void MoveFinder::AddMoveIfValidDestination(
		std::vector<Move>* moves,
		const Cell<int> &from,
		const Cell<int> &to,
		MoveType type)
	{
		// If there is a tile and it is empty, we can move the piece to it.
		if (((to.GetData()) & (IsEmpty | HasTile)) == (IsEmpty | HasTile)) {
			moves->push_back(Move(type, (from.GetPosition()), (to.GetPosition())));
		}
		// If there is no tile, we have to pick a tile to move to it.
		else if (((to.GetData()) & HasTile) == 0) {
			AddTileMoveMoves(moves, type, from, to);
		}
	}

	void MoveFinder::AddTileMoveMoves(std::vector<Move>* moves, MoveType type, Cell<int> from, Cell<int> to) {
		std::vector<Cell<int>>* emptyCells = _board->GetEmptyTiles();
		for (auto it = emptyCells->begin(); it != emptyCells->end(); ++it) {
			moves->push_back(Move(
				type,
				from.GetPosition(),
				to.GetPosition(),
				it->GetPosition()
			));
		}
	}
}
