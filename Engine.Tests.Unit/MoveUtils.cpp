#include "MoveUtils.h"

namespace engine {
	
	bool MovesAreEqual(Move moveA, Move moveB) {
		if (moveA.GetMoveType() != moveB.GetMoveType())
			return false;

		if (moveA.GetFromCell() != moveB.GetFromCell())
			return false;

		if (moveA.GetToCell() != moveB.GetToCell())
			return false;

		if (moveA.HasUsedCell() != moveB.HasUsedCell())
			return false;

		if (moveA.HasUsedCell() && moveA.GetUsedCell() != moveB.GetUsedCell())
			return false;

		return true;
	}
}