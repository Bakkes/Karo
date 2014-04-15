#pragma once

#include "MoveWrapper.h"
#include "IBoard.h"
using namespace engine;

namespace engine {
namespace wrapper {
	public ref class KaroGame
	{
		public:
			KaroGame();
			~KaroGame();
		private:
			IBoard * board;
	};
}
}