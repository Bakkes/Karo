#pragma once
#include "Move.h"
#include "Cell.h"
#include <vector>
#include "Players.h"
#include "Vector2D.h"
namespace engine {
enum CellValue{
	HasTile = 1,
	IsEmpty = 2,
	IsMax = 4,
	IsFlipped = 8
};
	class IBoard {
	public:
		virtual void ExecuteMove(Move* move, Players player) = 0;
		virtual std::vector<Move>* GetLegalMoves(Players player) = 0;
		virtual std::vector<Cell<int>>* GetOccupiedTiles() = 0;
		virtual Cell<int>* GetRelativeCellAt(const Vector2D relativePosition) const = 0;
	};
}
