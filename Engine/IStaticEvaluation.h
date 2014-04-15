#pragma once
#include "IBoard.h"
#include "Players.h"

namespace engine {
	class IStaticEvaluation {
	public:
		virtual ~IStaticEvaluation() {
		}
		// Creates a static evaluation from the given board for the given player.
		virtual int ENGINE_API Eval(IBoard* board, Players player) = 0;
	};
}