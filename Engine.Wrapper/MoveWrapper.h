#pragma once

#include "Move.h"
#include "Vector2DWrapper.h"
using namespace engine;

namespace engine {
namespace wrapper {

	public enum class MoveType { INSERT = 0, MOVE = 1, JUMP = 2};

	public ref class MoveWrapper
	{
		public:
			MoveWrapper(engine::wrapper::MoveType moveType, Vector2D fromCell, Vector2D toCell, Vector2D usedCell);
			~MoveWrapper();
			engine::wrapper::MoveType GetMoveType();
			engine::wrapper::Vector2DWrapper^ GetFromTile();
			engine::wrapper::Vector2DWrapper^ GetToTile();
			void SetToTile(engine::wrapper::Vector2DWrapper^ location);
			engine::wrapper::Vector2DWrapper^ GetUsedTile();
			bool HasUsedTile();
		private:
			Move * _move;
	};
}
}
