#include "TranspositionExtension.h"
#include "RngTimeBased.h"

namespace engine {

	TranspositionExtension::TranspositionExtension() {
		_transpositionTable = new TranspositionTable();
	}

	TranspositionExtension::~TranspositionExtension()
	{
		delete _transpositionTable;
		delete _hasher;
	}

	void TranspositionExtension::Start(const int& maxDepth, IBoard* board, IStaticEvaluation* evaluation) {
		AIExtension::Start(maxDepth, board, evaluation);
		IRng* rand = new RngTimeBased();
		_hasher = new ZobristHashing(board, rand);
		delete rand;
	}

	bool TranspositionExtension::ShouldContinue( const EvalResult& currentResult, EvalResult& prevResult, const Players& player) {
		return true;
	}
}
