#pragma once

#include "Grid.h"
#include "IBoard.h"
#include "MoveFinder.h"
#include <string>
#include <sstream>

using namespace std;
namespace engine{
	class MoveFinder;

	class ENGINE_API Board : public IBoard{
	public:
		static const int MaxPiecesPerPlayer = 6;

		Board();
		Board(bool init);
		~Board();
		int GetPieceCountFor(Players player) override;
		void ExecuteMove(Move *m, Players player) override;
		vector<Move>* GetLegalMoves(Players player) override;
		vector<Cell<int>>* GetOccupiedTiles() override;
		vector<Cell<int>>* GetEmptyTiles();
		int GetNumberOfEdges(Cell<int>*) override;
		Cell<int>* GetRelativeCellAt(const Vector2D relativePosition) const override;
		Cell<int>* GetAbsoluteCellAt(const Vector2D absolutePosition) const;
		string ToString();
		// create a board from a string with topleft at 0,0
		static Board* CreateBoard(string from);
		// allows you to specify the top left position, the string from is still absolute
		static Board*  CreateBoard(string from, Vector2D absoluteTopLeft);
		static const Size initSize;
	private:
		MoveFinder* _moveFinder;
		Grid<int>* _grid;
		void Init(bool init);
		void InsertPiece(const Cell<int>& on, Players owner);
		void DeletePiece(const Cell<int>& on);
		Vector2D _absoluteTopLeft;
		void InsertPiece(Cell<int>& on, Players owner);
		void DeletePiece(Cell<int>& on);
		void MovePiece(Cell<int>& from, Cell<int>& to, Players owner, Cell<int>& tileUsed);
		void MovePiece(Cell<int>& from, Cell<int>& to, Players owner);
		void JumpPiece(Cell<int>& from, Cell<int>& to, Players owner, Cell<int>& tileUsed);
		void JumpPiece(Cell<int>& from, Cell<int>& to, Players owner);
		void Flip(Cell<int>& which);
	};
}
