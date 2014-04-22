#include "MoveFinder.h"

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
		return nullptr;
	}

	std::vector<Move>* MoveFinder::GetLegalMoveMoves(Players player) {
		return nullptr;
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