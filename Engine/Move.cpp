#include "Move.h"

namespace Engine {
	Move::Move(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile) {
		init(moveType, fromTile, toTile, moveDirection, emptyTile);
	}

	void Move::init(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile) {
		_moveType = moveType;
		_fromTile = fromTile;
		_toTile = toTile;
		_moveDirection = moveDirection;
		_emptyTile = emptyTile;
	}
}