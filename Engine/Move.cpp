#include "Move.h"

namespace engine {
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

	MoveType Move::GetMoveType() {
		return _moveType;
	}

	int Move::GetFromTile() {
		return _fromTile;
	}

	int Move::GetToTile() {
		return _toTile;
	}

	MoveDirection Move::GetMoveDirection() {
		return _moveDirection;
	}

	int Move::GetEmptyTile() {
		return _emptyTile;
	}
}