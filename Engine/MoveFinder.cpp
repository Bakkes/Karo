#include "MoveFinder.h"
#include "Cell.h"

namespace engine {
	MoveFinder::MoveFinder(IBoard* board) {
		_board = board;
	}

	MoveFinder::~MoveFinder(void) {
	}

	std::vector<Move>* MoveFinder::GetLegalMoves(Players player) {
		if (_board->GetPieceCountFor(player) < 3) {
			return GetLegalPlaceMoves(player);
		}
		else {
			return GetLegalMoveMoves(player);
		}
	}

	std::vector<Move>* MoveFinder::GetLegalPlaceMoves(Players player) {
		std::vector<Move>* moves = new std::vector<Move>();
		return moves;
	}

	std::vector<Move>* MoveFinder::GetLegalMoveMoves(Players player) {
		std::vector<Move>* moves = new std::vector<Move>();
		std::vector<Cell<int>>* occupiedCells = _board->GetOccupiedCells();

		// Loop through all occupied cells.
		for (auto it = occupiedCells->begin(); it != occupiedCells->end(); ++it) {

			// If this cells contain a piece owned by player, continue.
			if ((player == Max && (*(it->GetData()) & IsMax) == IsMax) ||
				(player == Min && (*(it->GetData()) & IsMax) != IsMax))
			{

			}
		}
		return moves;
	}

	// Adds all adjecent move options.
	void MoveFinder::AddAdjecentMovesToVector(std::vector<Move>* moves, Cell<int> cell) {
		AddAdjecentMoveIfValidDestination(moves, cell, *cell.GetLeft());
		AddAdjecentMoveIfValidDestination(moves, cell, *cell.GetRight());
		AddAdjecentMoveIfValidDestination(moves, cell, *cell.GetTop());
		AddAdjecentMoveIfValidDestination(moves, cell, *cell.GetBottom());

		// Diagonal
		AddAdjecentMoveIfValidDestination(moves, cell, *cell.GetTop()->GetLeft());
		AddAdjecentMoveIfValidDestination(moves, cell, *cell.GetTop()->GetRight());
		AddAdjecentMoveIfValidDestination(moves, cell, *cell.GetBottom()->GetLeft());
		AddAdjecentMoveIfValidDestination(moves, cell, *cell.GetBottom()->GetRight());
	}

	// Assumes that the fromtile has a piece on it.
	void MoveFinder::AddAdjecentMoveIfValidDestination(std::vector<Move>* moves, const Cell<int> &from, const Cell<int> &to) {
		Move* move = nullptr;
		if (((*to.GetData()) & IsEmpty) == IsEmpty) {
			// TODO: If the destination is not a tile yet, move an unused tile.
			move = new Move(MOVE, *(from.GetPosition()), *(to.GetLeft()->GetPosition()));
			moves->push_back(*move);
			delete move;
			move = nullptr;
		}
	}

	std::vector<Move> MoveFinder::FindMove(Cell<int> one,Cell<int> two) {
		std::vector<Move> possibility = std::vector<Move>();

		int checkRight = *one.GetData();
		if(!( checkRight & IsEmpty)) {
			int jumpRight = *two.GetData();
			if(jumpRight & IsEmpty) {
				if(jumpRight & HasCell) {
					possibility.push_back(Move(JUMP,*two.GetPosition()));
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
			possibility.push_back(Move(MOVE,*one.GetPosition()));
		}
		return possibility;
	}
}