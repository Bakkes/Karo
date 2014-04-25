#include "MoveFinder.h"
#include "Cell.h"

namespace engine {
	MoveFinder::MoveFinder(Board* board) {
		_board = board;
	}

	MoveFinder::~MoveFinder(void) {
	}

	std::vector<Move>* MoveFinder::GetLegalMoves(Players player) {
		if (_board->GetPieceCountFor(player) < 6) {
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
		AddMoveIfValidDestination(moves, source, *source.GetLeft()->GetLeft(), JUMP);
		AddMoveIfValidDestination(moves, source, *source.GetRight()->GetRight(), JUMP);
		AddMoveIfValidDestination(moves, source, *source.GetTop()->GetTop(), JUMP);
		AddMoveIfValidDestination(moves, source, *source.GetBottom()->GetBottom(), JUMP);

		// Diagonal
		AddMoveIfValidDestination(moves, source, *source.GetTop()->GetTop()->GetLeft()->GetLeft(), JUMP);
		AddMoveIfValidDestination(moves, source, *source.GetTop()->GetTop()->GetRight()->GetRight(), JUMP);
		AddMoveIfValidDestination(moves, source, *source.GetBottom()->GetBottom()->GetLeft()->GetLeft(), JUMP);
		AddMoveIfValidDestination(moves, source, *source.GetBottom()->GetBottom()->GetRight()->GetRight(), JUMP);
	}

	// Adds all adjecent move options.
	void MoveFinder::AddAdjecentMovesToVector(std::vector<Move>* moves, Cell<int> cell) {
		AddMoveIfValidDestination(moves, cell, *cell.GetLeft(), MOVE);
		AddMoveIfValidDestination(moves, cell, *cell.GetRight(), MOVE);
		AddMoveIfValidDestination(moves, cell, *cell.GetTop(), MOVE);
		AddMoveIfValidDestination(moves, cell, *cell.GetBottom(), MOVE);

		// Diagonal
		AddMoveIfValidDestination(moves, cell, *cell.GetTop()->GetLeft(), MOVE);
		AddMoveIfValidDestination(moves, cell, *cell.GetTop()->GetRight(), MOVE);
		AddMoveIfValidDestination(moves, cell, *cell.GetBottom()->GetLeft(), MOVE);
		AddMoveIfValidDestination(moves, cell, *cell.GetBottom()->GetRight(), MOVE);
	}

	// Assumes that the fromtile has a piece on it.
	void MoveFinder::AddMoveIfValidDestination(
		std::vector<Move>* moves,
		const Cell<int> &from,
		const Cell<int> &to,
		MoveType type)
	{
		// If there is a tile and it is empty, we can move the piece to it.
		if (((to.GetData()) & (IsEmpty | HasCell)) == (IsEmpty | HasCell)) {
			moves->push_back(Move(type, (from.GetPosition()), (to.GetPosition())));
		}
		// If there is no tile, we have to pick a tile to move to it.
		else if (((to.GetData()) & HasCell) == 0) {
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

	std::vector<Move> MoveFinder::FindMove(Cell<int> one,Cell<int> two) {
		std::vector<Move> possibility = std::vector<Move>();

		int checkRight = one.GetData();
		if(!( checkRight & IsEmpty)) {
			int jumpRight = two.GetData();
			if(jumpRight & IsEmpty) {
				if(jumpRight & HasCell) {
					possibility.push_back(Move(JUMP, two.GetPosition()));
				}
				else {
				//	ForPickableTiles(
				//	[&](Tile<int>* tile) -> void{
				//		possibility.push_back(Move(JUMP,*two.GetPosition()));
				//});
				}
			}
		}
		else {
			possibility.push_back(Move(MOVE, one.GetPosition()));
		}
		return possibility;
	}
}