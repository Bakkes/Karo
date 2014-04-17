#include "RandStaticEval.h"

namespace engine {
	RandStaticEval::RandStaticEval() {
	}

	RandStaticEval::~RandStaticEval()	{
	}

	int RandStaticEval::Eval(IBoard* board, Players player) {
		return rand();
	}
}
