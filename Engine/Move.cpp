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
		Vector2D difference = fromCell-toCell;
				if(abs(difference.X())>2)
				{
					toCell.X(-1);
				}
				if(abs(difference.Y())>2)
				{
					toCell.Y(-1);
				}

		_moveType = type;
		_fromCell = fromCell;
		_toCell = toCell;
		_usedCell = usedCell;
		_hasUsedCell = hasUsedCell;
	}

	const MoveType& Move::GetMoveType() const {
		return _moveType;
	}

	const Vector2D& Move::GetFromCell() const {
		return _fromCell;
	}

	const Vector2D& Move::GetToCell() const {
		return _toCell;
	}

	const Vector2D& Move::GetUsedCell() const {
#ifdef _DEBUG
		if (!HasUsedCell()) {
			throw "Called GetUsedCell whilst no tile is being used";
		}
#endif
		return _usedCell;
	}

	const bool& Move::HasUsedCell() const {
		return _hasUsedCell;
	}
}
