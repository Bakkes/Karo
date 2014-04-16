#pragma once

#include "Move.h"
using namespace engine;

namespace engine {
namespace wrapper {

	public enum class MoveType { INSERT = 0, MOVE = 1, JUMP = 2};

	public ref class MoveWrapper
	{
		public:
			MoveWrapper(engine::wrapper::MoveType moveType, Vector2D fromTile, Vector2D toTile, Vector2D usedTile);
			~MoveWrapper();
			engine::wrapper::MoveType GetMoveType();
			Vector2D GetFromTile();
			Vector2D GetToTile();
			Vector2D GetUsedTile();
			bool HasUsedTile();
		private:
			Move * _move;
	};
}
}