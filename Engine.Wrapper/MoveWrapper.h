#pragma once

#include "Move.h"
#include "Vector2DWrapper.h"
using namespace engine;

namespace engine {
namespace wrapper {

	public enum class MoveType { INSERT = 0, STEP = 1, JUMP = 2};

	public ref class MoveWrapper
	{
		public:
			MoveWrapper(engine::wrapper::MoveType moveType, Vector2D fromCell, Vector2D toCell, Vector2D usedCell, bool hasUsedTile);
			MoveWrapper(engine::wrapper::MoveType moveType, Vector2DWrapper^ fromTile, Vector2DWrapper^ toTile, Vector2DWrapper^ usedTile);
			MoveWrapper(engine::wrapper::MoveType moveType, Vector2DWrapper^ fromTile, Vector2DWrapper^ toTile);
			~MoveWrapper();
			engine::wrapper::MoveType GetMoveType();
			engine::wrapper::Vector2DWrapper^ GetFromCell();
			engine::wrapper::Vector2DWrapper^ GetToCell();
			engine::wrapper::Vector2DWrapper^ GetUsedCell();
			bool HasUsedCell();
		private:
			Move * _move;
	};
}
}
