#include "Move.h"

namespace engine {

	Move::Move(MoveType type, Vector2D toCell) {
		Init(type, Vector2D(-1), toCell, Vector2D(-1), false);
	}

	Move::Move(MoveType type, Vector2D fromCell, Vector2D toCell) {
		Init(type, fromCell, toCell, Vector2D(-1), false);
	}

	Move::Move(MoveType type, Vector2D fromCell, Vector2D toCell, Vector2D usedCell) {
		Init(type, fromCell, toCell, usedCell, true);
	}

	void Move::Init(MoveType type, Vector2D fromCell, Vector2D toCell, Vector2D usedCell, bool hasUsedCell) {
		_moveType = type;
		_fromCell = fromCell;
		_toCell = toCell;
		_usedCell = usedCell;
		_hasUsedCell = hasUsedCell;
	}

	MoveType Move::GetMoveType() const {
		return _moveType;
	}

	Vector2D Move::GetFromCell() const {
		return _fromCell;
	}

	Vector2D Move::GetToCell() const {
		return _toCell;
	}

	Vector2D Move::GetUsedCell() const {
#ifdef _DEBUG
		if (!HasUsedCell())
			throw "Called GetUsedCell whilst no tile is being used";
#endif
		return _usedCell;
	}

	bool Move::HasUsedCell() const {
		return _hasUsedCell;
	}
}
