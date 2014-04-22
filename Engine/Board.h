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
		vector<Tile<int>>* GetOccupiedTiles() override;
		Tile<int>* GetRelativeTileAt(const Vector2D relativePosition) const override;
		string ToString();
		static Board* CreateBoard(string from);
	private:
		Grid<int>* _grid;
		Vector2D absoluteTopLeft;
		void InsertPiece(const Tile<int>& on, Players owner);
		void DeletePiece(const Tile<int>& on);
		void MovePiece(const Tile<int>& from, const Tile<int>& to, Players owner, const Tile<int>& tileUsed);
		void MovePiece(const Tile<int>& from, const Tile<int>& to, Players owner);
		void JumpPiece(const Tile<int>& from, const Tile<int>& to, Players owner, const Tile<int>& tileUsed);
		void JumpPiece(const Tile<int>& from, const Tile<int>& to, Players owner);
		static const Size initSize;
	};

}
