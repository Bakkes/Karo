#include "stdafx.h"
#include "MoveWrapper.h"

namespace engine {
namespace wrapper {

MoveWrapper::MoveWrapper(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile)
{
	_move = new Move((engine::MoveType)moveType, fromTile, toTile, (engine::MoveDirection)moveDirection, (engine::MoveType)emptyTile);
}

MoveType MoveWrapper::GetMoveType() {
	return (engine::wrapper::MoveType)_move->GetMoveType();
}

int MoveWrapper::GetFromTile() {
	return _move->GetFromTile();
}

int MoveWrapper::GetToTile() {
	return _move->GetToTile();
}

MoveDirection MoveWrapper::GetMoveDirection() {
	return (engine::wrapper::MoveDirection)_move->GetMoveDirection();
}

int MoveWrapper::GetEmptyTile() {
	return _move->GetEmptyTile();
}

}
}