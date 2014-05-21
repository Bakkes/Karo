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
		void ExecuteMove(const Move& move, Players player) override;
		void UndoMove(const Move& m, Players player) override;
		void CreateTileAt(const Vector2D &relativePosition) override;
		void DeleteTileAt(const Vector2D &relativePosition) override;
		std::vector<Move> GetLegalMoves(Players player) override;
		std::vector<RelativeCell>* GetOccupiedTiles() override;
		std::vector<RelativeCell>* GetEmptyTiles() override;
		int CountNonDiagonalEdges(const RelativeCell&) override;
		RelativeCell GetRelativeCellAt(const Vector2D& relativePosition) const override;
		Vector2D GetDynamicSize() override;
	private:
		bool _minimalMoves;
		int _moveIdentifier; 
	};
}
