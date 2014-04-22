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
		Board();
		~Board();
		int GetPieceCountFor(Players player) override;
		void ExecuteMove(Move *m, Players player) override;
		vector<Move>* GetLegalMoves(Players player) override;
		vector<Cell<int>>* GetOccupiedCells() override;
		Cell<int>* GetRelativeCellAt(const Vector2D relativePosition) const override;
		string ToString();
		static Board* CreateBoard(string from);
	private:
		MoveFinder* _moveFinder;
		Grid<int>* _grid;
		Vector2D absoluteTopLeft;
		void InsertPiece(const Cell<int>& on, Players owner);
		void DeletePiece(const Cell<int>& on);
		void MovePiece(const Cell<int>& from, const Cell<int>& to, Players owner, const Cell<int>& tileUsed);
		void MovePiece(const Cell<int>& from, const Cell<int>& to, Players owner);
		void JumpPiece(const Cell<int>& from, const Cell<int>& to, Players owner, const Cell<int>& tileUsed);
		void JumpPiece(const Cell<int>& from, const Cell<int>& to, Players owner);
		static const Size initSize;
	};

}
