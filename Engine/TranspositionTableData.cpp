#include "TranspositionTableData.h"

namespace engine {

	TranspositionTableData::TranspositionTableData(int score, Move* bestMove, int depth) {
		_score = score;
		_bestMove = bestMove;
		_depth = depth;
	}


	TranspositionTableData::~TranspositionTableData(void) {
		delete _bestMove;
	}
	
	Move* TranspositionTableData::GetBestMove() {
		return _bestMove;
	}

	int TranspositionTableData::GetScore() {
		return _score;
	}

	int TranspositionTableData::GetDepth() {
		return _depth;
	}
}
