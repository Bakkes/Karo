#pragma once
#include "IBoard.h"
#include "Players.h"

namespace engine {
	class ENGINE_API IStaticEvaluation {
	public:
		virtual ~IStaticEvaluation() {
		}
		// Creates a static evaluation from the given board for the given player.
		int Eval(IBoard* board, Players player);
	};
}