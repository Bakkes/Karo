#pragma once

#include "Move.h"
#include "MoveWrapper.h"
#include "Tile.h"
#include "TileWrapper.h"

namespace engine {
namespace wrapper{

class WrapperConversionUtility {
public:
	static Move* ConvertMove(MoveWrapper^ moveWrapper) {
		return new engine::Move(static_cast<engine::MoveType>(moveWrapper->GetMoveType()), 
			moveWrapper->GetFromTile(), moveWrapper->GetToTile(), 
			static_cast<engine::MoveDirection>(moveWrapper->GetMoveDirection()), moveWrapper->GetEmptyTile());
	}

	static MoveWrapper^ ConvertMove(Move* move) {
		return gcnew MoveWrapper(static_cast<engine::wrapper::MoveType>(move->GetMoveType()), 
			move->GetFromTile(), move->GetToTile(), static_cast<engine::wrapper::MoveDirection>(move->GetMoveDirection()), 
			move->GetEmptyTile());
	}

	static MoveWrapper^ ConvertMove(Move move) {
		return gcnew MoveWrapper(static_cast<engine::wrapper::MoveType>(move.GetMoveType()), 
			move.GetFromTile(), move.GetToTile(), static_cast<engine::wrapper::MoveDirection>(move.GetMoveDirection()), 
			move.GetEmptyTile());
	}

	static TileWrapper^ ConvertTile(Tile<int> tile) {
		return gcnew TileWrapper(tile.GetPosition()->X(), tile.GetPosition()->Y());
	}

	static Tile<int>* ConvertTile(TileWrapper^ tile) {
		return new Tile<int>(new Vector2D(tile->GetPosition()->Y, tile->GetPosition()->X));
	}
};

}
}