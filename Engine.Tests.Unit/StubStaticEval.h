#pragma once

#include "IStaticEvaluation.h"

namespace engine {

	class StubStaticEval : public IStaticEvaluation {
	public:
		StubStaticEval();
		~StubStaticEval();

		int Eval(IBoard* board, Players player) override;

	};
}
