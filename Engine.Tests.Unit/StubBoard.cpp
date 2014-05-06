#include "StubBoard.h"

namespace Tests {

	StubBoard::StubBoard() {
	}

	StubBoard::~StubBoard() {
	}

	int StubBoard::GetPieceCountFor(Players player) {
		return 0;
	}

	void StubBoard::ExecuteMove(Move* move, Players player) {
	}

	std::vector<Move>* StubBoard::GetLegalMoves(Players player) {
		std::vector<Move>* legalMoves = new std::vector<Move>();

		legalMoves->push_back(Move(MOVE, Vector2D(0), Vector2D(0, 1)));
		legalMoves->push_back(Move(MOVE, Vector2D(0), Vector2D(1, 0)));
		legalMoves->push_back(Move(JUMP, Vector2D(0), Vector2D(0, 2)));

		return legalMoves;
	}

	std::vector<Cell<int>>* StubBoard::GetOccupiedTiles() {
		return nullptr;
	}

	int StubBoard::GetNumberOfEdges(Cell<int>*) {
		return 0;
	}

	Cell<int>* StubBoard::GetRelativeCellAt(const Vector2D relativePosition) const {
		return nullptr;
	}
}