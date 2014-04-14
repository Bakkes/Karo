#pragma once
#include "IUnsafeBoard.h"
#include "Players.h"

namespace engine {
	class IStaticEvaluation {
	public:
		virtual ~IStaticEvaluation();
		// Creates a static evaluation from the given board for the given player.
		int Eval(IUnsafeBoard board, Players player);
	};
}