#pragma once

#include "Grid.h"
#include "IBoard.h"
#include "RelativeCell.h"
#include "MoveFinder.h"
#include <string>
#include <sstream>
#include "RelativeAbsoluteConverter.h"
#include "CellValue.h"

using namespace std;
namespace engine{
	class MoveFinder;

	class ENGINE_API Board : public IBoard{
	public:
		Board();
		Board(const Board& cpy);
		Board(bool init);
		~Board();
		int GetPieceCountFor(Players player) override;
		void ExecuteMove(const Move& m, Players player) override;
		void UndoMove(const Move& m, Players player) override;
		void CreateTileAt(const Vector2D &relativePosition) override;
		void DeleteTileAt(const Vector2D &relativePosition) override;
		vector<Move> GetLegalMoves(Players player) override;
		vector<RelativeCell>* GetOccupiedTiles() override;
		vector<RelativeCell>* GetEmptyTiles() override;
		RelativeCell GetRelativeCellAt(const Vector2D& relativePosition) const override;
		int CountNonDiagonalEdges(const RelativeCell&) override;
		Cell<int>* GetAbsoluteCellAt(const Vector2D absolutePosition) const;
		string ToString() const;
		// create a board from a string with topleft at 0,0
		static Board* CreateBoard(string from);
		// allows you to specify the top left position, the string from is still absolute
		static Board*  CreateBoard(string from, Vector2D absoluteTopLeft);
		static const Size initSize;
		Vector2D GetDynamicSize() override;
		int GetWidth();
		int GetHeight();
	private:
		MoveFinder* _moveFinder;
		RelativeAbsoluteConverter* _converter;
		Grid<int>* _grid;
		void Init(bool init);
		void InsertPiece(const Cell<int>& on, Players owner);
		void DeletePiece(const Cell<int>& on);
		void MoveTile(Cell<int>& from, Cell<int>& to);
		void InsertPiece(Cell<int>& on, Players owner);
		void DeletePiece(Cell<int>& on);
		void MovePiece(Cell<int>& from, Cell<int>& to, Players owner, Cell<int>& tileUsed);
		void MovePiece(Cell<int>& from, Cell<int>& to, Players owner);
		void JumpPiece(Cell<int>& from, Cell<int>& to, Players owner, Cell<int>& tileUsed);
		void JumpPiece(Cell<int>& from, Cell<int>& to, Players owner);
		void Flip(Cell<int>& which);
		Move ShiftMoveBack(const Move&);
	};
}
