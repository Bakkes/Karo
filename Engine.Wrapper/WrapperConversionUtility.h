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
			moveWrapper->GetFromTile(), moveWrapper->GetToTile(), moveWrapper->GetUsedTile());
	}

	static MoveWrapper^ ConvertMove(Move* move) {
		return gcnew MoveWrapper(static_cast<engine::wrapper::MoveType>(move->GetMoveType()), 
			move->GetFromTile(), move->GetToTile(), move->GetUsedTile());
	}

	static MoveWrapper^ ConvertMove(Move move) {
		return gcnew MoveWrapper(static_cast<engine::wrapper::MoveType>(move.GetMoveType()), 
			move.GetFromTile(), move.GetToTile(), move.GetUsedTile());
	}

	static TileWrapper^ ConvertTile(Tile<int> tile) {
		return gcnew TileWrapper(tile.GetPosition()->X(), tile.GetPosition()->Y());
	}

	static TileWrapper^ ConvertTile(Tile<int>* tile) {
		return gcnew TileWrapper(tile->GetPosition()->X(), tile->GetPosition()->Y());
	}

	static Tile<int>* ConvertTile(TileWrapper^ tile) {
		return new Tile<int>(new Vector2D(tile->GetPosition()->Y, tile->GetPosition()->X));
	}

	static Vector2DWrapper^ ConvertVector2D(Vector2D* vector2d) {
		return gcnew Vector2DWrapper(vector2d->X(), vector2d->Y());
	}

	static Vector2D* ConvertVector2D(Vector2DWrapper^ vector2d) {
		return new Vector2D(vector2d->X, vector2d->Y);
	}
};

}
}