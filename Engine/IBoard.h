#pragma once
#include "Move.h"
#include "Tile.h"
namespace engine {
enum TileValue{
	HasTile = 1,
	IsEmpty = 2,
	IsMax = 4,
	IsFlipped = 8
};
	class IBoard {
		virtual void ExecuteMove(Move* move) = 0;
		virtual std::vector<Move>* GetLegalMoves() = 0;
		virtual std::vector<Tile<int>>* GetOccupiedTiles() = 0;
	};
}