#include "RandStaticEval.h"

namespace engine {
	RandStaticEval::RandStaticEval() {
		srand(0);
	}

	RandStaticEval::~RandStaticEval()	{
	}

	int RandStaticEval::Eval(IBoard* board, Players player) {
		return rand();
	}
}
