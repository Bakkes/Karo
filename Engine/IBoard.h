#pragma once
#include "Move.h"
#include "Cell.h"
#include <vector>
#include "Players.h"
#include "Vector2D.h"
#include "RelativeCell.h"
namespace engine {
	class IBoard {
	public:
		virtual int GetPieceCountFor(Players player) = 0;
		virtual void ExecuteMove(Move* move, Players player) = 0;
		virtual std::vector<Move>* GetLegalMoves(Players player) = 0;
		virtual std::vector<RelativeCell>* GetOccupiedTiles() = 0;
		virtual int CountNonDiagonalEdges(const RelativeCell&) = 0;
		virtual RelativeCell GetRelativeCellAt(const Vector2D& relativePosition) const = 0;
	};
}
