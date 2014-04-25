#include "StubStaticEval.h"

namespace engine {
	StubStaticEval::StubStaticEval() {
		srand(0);
	}

	StubStaticEval::~StubStaticEval()	{
	}

	int StubStaticEval::Eval(IBoard* board, Players player) {
		return rand();
	}
}
