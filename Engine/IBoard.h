#pragma once
#include "Move.h"
#include "Tile.h"
#include <vector>
#include "Players.h"
namespace engine {
enum TileValue{
	HasTile = 1,
	IsEmpty = 2,
	IsMax = 4,
	IsFlipped = 8
};
	class IBoard {
	public:
		virtual void ExecuteMove(Move* move, Players player) = 0;
		virtual std::vector<Move>* GetLegalMoves(Players player) = 0;
		virtual std::vector<Tile<int>>* GetOccupiedTiles() = 0;
	};
}
