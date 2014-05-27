#include "TranspositionExtension.h"
#include "RngTimeBased.h"

namespace engine {

	TranspositionExtension::TranspositionExtension() {
		IRng* rand = new RngTimeBased();

		delete rand;
	}


	TranspositionExtension::~TranspositionExtension()
	{
	}

	bool TranspositionExtension::ShouldContinue(const IBoard* board, const EvalResult& currentResult, EvalResult& prevResult, const Players& player) {
		return true;
	}
}
