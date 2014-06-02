#include "TranspositionTableData.h"

namespace engine {

	TranspositionTableData::TranspositionTableData(int score, Move* bestMove) {
		_score = score;
		_bestMove = bestMove;
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
}
