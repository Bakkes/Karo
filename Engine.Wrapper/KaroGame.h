#pragma once

#include "MoveWrapper.h"
#include "Board.h"
using namespace engine;

namespace engine {
namespace wrapper {
	public ref class KaroGame
	{
		public:
			KaroGame();
			~KaroGame();
		private:
			Board * _board;
	};
}
}