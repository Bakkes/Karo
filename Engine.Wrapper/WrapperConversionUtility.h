#pragma once

#include "Move.h"
#include "MoveWrapper.h"
#include "Cell.h"
#include "CellWrapper.h"

namespace engine {
namespace wrapper{

class WrapperConversionUtility {
public:
	static Move* ConvertMove(MoveWrapper^ moveWrapper) {
		if (moveWrapper->HasUsedCell()) {
			return new engine::Move(
				static_cast<engine::MoveType>(moveWrapper->GetMoveType()), 
				ConvertVector2DStack(moveWrapper->GetFromCell()),
				ConvertVector2DStack(moveWrapper->GetToCell()),
				ConvertVector2DStack(moveWrapper->GetUsedCell())
			);
		}
		else {
			return new engine::Move(
				static_cast<engine::MoveType>(moveWrapper->GetMoveType()), 
				ConvertVector2DStack(moveWrapper->GetFromCell()),
				ConvertVector2DStack(moveWrapper->GetToCell())
			);
		}
	}

	static MoveWrapper^ ConvertMove(Move* move) {
		return gcnew MoveWrapper(static_cast<engine::wrapper::MoveType>(move->GetMoveType()), 
			move->GetFromCell(), move->GetToCell(), move->HasUsedCell() ? move->GetUsedCell() : 0, move->HasUsedCell());
	}

	static MoveWrapper^ ConvertMove(Move move) {
		return gcnew MoveWrapper(static_cast<engine::wrapper::MoveType>(move.GetMoveType()), 
			move.GetFromCell(), move.GetToCell(), move.HasUsedCell() ? move.GetUsedCell() : 0, move.HasUsedCell());
	}

	static CellWrapper^ ConvertCell(Cell<int> cell) {
		return gcnew CellWrapper(cell);
	}

	static CellWrapper^ ConvertCell(Cell<int>* cell) {
		return ConvertCell(*cell);
	}

	static Vector2DWrapper^ ConvertVector2D(Vector2D vector2d) {
		return gcnew Vector2DWrapper(vector2d.X(), vector2d.Y());
	}

	static Vector2DWrapper^ ConvertVector2D(Vector2D* vector2d) {
		return gcnew Vector2DWrapper(vector2d->X(), vector2d->Y());
	}

	static Vector2D* ConvertVector2D(Vector2DWrapper^ vector2d) {
		return new Vector2D(vector2d->X, vector2d->Y);
	}

	static Vector2D ConvertVector2DStack(Vector2DWrapper^ vector2d) {
		return Vector2D(vector2d->X, vector2d->Y);
	}
};

}
}