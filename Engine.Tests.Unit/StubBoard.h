#pragma once
#include "IBoard.h"
using namespace engine;

namespace Tests {

	class StubBoard : public IBoard {
	public:
		StubBoard();
		StubBoard(bool minimalMoves);
		~StubBoard();

		int GetPieceCountFor(Players player) override;
		void ExecuteMove(Move* move, Players player) override;
		std::vector<Move> GetLegalMoves(Players player) override;
		std::vector<RelativeCell>* GetOccupiedTiles() override;
		std::vector<RelativeCell>* GetEmptyTiles() override;
		int CountNonDiagonalEdges(const RelativeCell&) override;
		RelativeCell GetRelativeCellAt(const Vector2D& relativePosition) const override;

	private:
		bool _minimalMoves;
	};
}
