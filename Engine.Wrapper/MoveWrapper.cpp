#include "stdafx.h"
#include "MoveWrapper.h"

namespace engine {
namespace wrapper {

MoveWrapper::MoveWrapper(Move * move)
{
	_move = move;
}

MoveWrapper::MoveWrapper(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile)
{
	_move = new engine::Move(static_cast<engine::MoveType>(moveType), fromTile, toTile, static_cast<engine::MoveDirection>(moveDirection), emptyTile);
}

MoveWrapper::~MoveWrapper() {
	delete _move;
}

engine::wrapper::MoveType MoveWrapper::GetMoveType() {
	return static_cast<engine::wrapper::MoveType>(_move->GetMoveType());
}

int MoveWrapper::GetFromTile() {
	return _move->GetFromTile();
}

int MoveWrapper::GetToTile() {
	return _move->GetToTile();
}

engine::wrapper::MoveDirection MoveWrapper::GetMoveDirection() {
	return static_cast<engine::wrapper::MoveDirection>(_move->GetMoveDirection());
}

int MoveWrapper::GetEmptyTile() {
	return _move->GetEmptyTile();
}

}
}