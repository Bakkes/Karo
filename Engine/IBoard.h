#pragma once
#include "Move.h"
#include <vector>
#include "Players.h"
#include "Vector2D.h"
#include "RelativeCell.h"
namespace engine {
	class IBoard {
	public:
		static const int MaxPiecesPerPlayer = 6;
		virtual int GetPieceCountFor(Players player) = 0;
		virtual void ExecuteMove(const Move& m, Players player) = 0;
		virtual void UndoMove(const Move& m, Players player) = 0;
		virtual void CreateTileAt(const Vector2D &relativePosition) = 0;
		virtual void DeleteTileAt(const Vector2D &relativePosition) = 0;
		virtual std::vector<Move> GetLegalMoves(Players player) = 0;
		virtual std::vector<RelativeCell>* GetOccupiedTiles() = 0;
		virtual std::vector<RelativeCell>* GetEmptyTiles() = 0;
		virtual int CountNonDiagonalEdges(const RelativeCell&) = 0;
		virtual RelativeCell GetRelativeCellAt(const Vector2D& relativePosition) const = 0;
	};
}
