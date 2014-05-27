#include "TranspositionExtension.h"

namespace engine {

	TranspositionExtension::TranspositionExtension() {
		_hasher = new ZobristHashing();
	}


	TranspositionExtension::~TranspositionExtension()
	{
	}

	bool TranspositionExtension::ShouldContinue(const IBoard* board, const EvalResult& currentResult, EvalResult& prevResult, const Players& player) {
		return true;
	}
}
