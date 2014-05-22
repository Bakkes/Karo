#include "StubBoard.h"

namespace Tests {

	StubBoard::StubBoard() {
		_minimalMoves = false;
	}

	StubBoard::StubBoard(bool minimalMoves) {
		_minimalMoves = minimalMoves;
	}

	StubBoard::~StubBoard() {
	}

	int StubBoard::GetPieceCountFor(Players player) {
		return 0;
	}

	void StubBoard::CreateTileAt(const Vector2D &relativePosition) { }
	void StubBoard::DeleteTileAt(const Vector2D &relativePosition) { }

	void StubBoard::ExecuteMove(const Move& move, Players player) { }
	void StubBoard::UndoMove(const Move& move, Players player) { }

	std::vector<Move> StubBoard::GetLegalMoves(Players player) {
		std::vector<Move> legalMoves = std::vector<Move>();

		legalMoves.push_back(Move(STEP, Vector2D(0), Vector2D(0, 1)));
		legalMoves.push_back(Move(STEP, Vector2D(0), Vector2D(1, 0)));
		if (!_minimalMoves) {
			legalMoves.push_back(Move(JUMP, Vector2D(0), Vector2D(0, 2)));
		}

		return legalMoves;
	}

	std::vector<RelativeCell>* StubBoard::GetOccupiedTiles() {
		return nullptr;
	}

	int StubBoard::CountNonDiagonalEdges(const RelativeCell&) {
		return 0;
	}

	void StubBoard::SetMinimalMoves(const bool& to){
		_minimalMoves = to;
	}
	RelativeCell StubBoard::GetRelativeCellAt(const Vector2D& relativePosition) const {
		return RelativeCell(nullptr, nullptr);
	}
	std::vector<RelativeCell>* StubBoard::GetEmptyTiles(){
		return nullptr;
	}
}
