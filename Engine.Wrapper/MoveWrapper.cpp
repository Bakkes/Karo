#include "stdafx.h"
#include "MoveWrapper.h"

namespace engine {
namespace wrapper {

	MoveWrapper::MoveWrapper(MoveType moveType, Vector2D fromTile, Vector2D toTile, Vector2D usedTile) {
		_move = new engine::Move(static_cast<engine::MoveType>(moveType), fromTile, toTile, usedTile);
	}

	MoveWrapper::~MoveWrapper() {
		delete _move;
	}

	engine::wrapper::MoveType MoveWrapper::GetMoveType() {
		return static_cast<engine::wrapper::MoveType>(_move->GetMoveType());
	}

	Vector2D MoveWrapper::GetFromTile() {
		return _move->GetFromTile();
	}

	Vector2D MoveWrapper::GetToTile() {
		return _move->GetToTile();
	}

	Vector2D MoveWrapper::GetUsedTile() {
		return _move->GetUsedTile();
	}

	bool MoveWrapper::HasUsedTile() {
		return _move->HasUsedTile();
	}

}
}