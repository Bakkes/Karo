#include "Move.h"

namespace engine {

	Move::Move(MoveType type, Vector2D toTile) {
		Init(type, Vector2D(-1), toTile, Vector2D(-1), false);
	}

	Move::Move(MoveType type, Vector2D fromTile, Vector2D toTile) {
		Init(type, fromTile, toTile, Vector2D(-1), false);
	}

	Move::Move(MoveType type, Vector2D fromTile, Vector2D toTile, Vector2D usedTile) {
		Init(type, fromTile, toTile, usedTile, true);
	}

	void Move::Init(MoveType type, Vector2D fromTile, Vector2D toTile, Vector2D usedTile, bool hasUsedTile) {
		_moveType = type;
		_fromTile = fromTile;
		_toTile = toTile;
		_usedTile = usedTile;
		_hasUsedTile = hasUsedTile;
	}

	MoveType Move::GetMoveType() {
		return _moveType;
	}

	Vector2D Move::GetFromTile() {
		return _fromTile;
	}

	Vector2D Move::GetToTile(){
		return _toTile;
	}

	void Move::SetToTile(Vector2D location) {
		_toTile = location;
	}

	Vector2D Move::GetUsedTile(){
		return _usedTile;
	}

	bool Move::HasUsedTile() {
		return _hasUsedTile;
	}
}