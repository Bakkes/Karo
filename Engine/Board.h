#include "Grid.h"
#include "IBoard.h"
#include <string>
#include <sstream>
#pragma once
using namespace std;
namespace engine{

	class ENGINE_API Board : public IBoard{
	public:
		Board();
		~Board();
		void ExecuteMove(Move *m, Players player) override;
		vector<Move>* GetLegalMoves(Players player) override;
		vector<Cell<int>>* GetOccupiedCells() override;
		Cell<int>* GetRelativeCellAt(const Vector2D relativePosition) const override;
		string ToString();
		// create a board from a string with topleft at 0,0
		static Board* CreateBoard(string from);
		// allows you to specify the top left position, the string from is still absolute
		static Board* CreateBoard(string from, Vector2D absoluteTopLeft);
	private:
		Board(bool init);
		void Init(bool);
		Grid<int>* _grid;
		Vector2D _absoluteTopLeft;
		void InsertPiece(const Cell<int>& on, Players owner);
		void DeletePiece(const Cell<int>& on);
		void MovePiece(const Cell<int>& from, const Cell<int>& to, Players owner, const Cell<int>& tileUsed);
		void MovePiece(const Cell<int>& from, const Cell<int>& to, Players owner);
		void JumpPiece(const Cell<int>& from, const Cell<int>& to, Players owner, const Cell<int>& tileUsed);
		void JumpPiece(const Cell<int>& from, const Cell<int>& to, Players owner);
		static const Size initSize;
	};

}
