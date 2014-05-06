#pragma once
#include "iboard.h"

using namespace engine;

namespace Tests {

	class StubBoard : public IBoard {
	public:
		StubBoard();
		StubBoard(bool minimalMoves);
		~StubBoard();

		int GetPieceCountFor(Players player);
		void ExecuteMove(Move* move, Players player);
		std::vector<Move>* GetLegalMoves(Players player);
		std::vector<Cell<int>>* GetOccupiedTiles();
		int GetNumberOfEdges(Cell<int>*);
		Cell<int>* GetRelativeCellAt(const Vector2D relativePosition) const;

	private:
		bool _minimalMoves;
	};
}
