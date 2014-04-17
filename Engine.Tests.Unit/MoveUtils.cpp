#include "MoveUtils.h"

namespace engine {
	
	bool MovesAreEqual(Move moveA, Move moveB) {
		if (moveA.GetMoveType() != moveB.GetMoveType())
			return false;

		if (moveA.GetFromTile() != moveB.GetFromTile())
			return false;

		if (moveA.GetToTile() != moveB.GetToTile())
			return false;

		if (moveA.HasUsedTile() != moveB.HasUsedTile())
			return false;

		if (moveA.HasUsedTile() && moveA.GetUsedTile() != moveB.GetUsedTile())
			return false;

		return true;
	}
}