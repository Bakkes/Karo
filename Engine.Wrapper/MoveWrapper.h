#pragma once
#include "Move.h"
using namespace engine;

namespace engine {
namespace wrapper {

	public enum class MoveType { INSERT = 0, MOVE = 1, JUMP = 2};
	public enum class MoveDirection { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };

	public ref class MoveWrapper
	{
		public:
			MoveWrapper(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile);
			MoveType GetMoveType();
			int GetFromTile();
			int GetToTile();
			MoveDirection GetMoveDirection();
			int GetEmptyTile();
		private:
			Move * _move;
	};
}
}