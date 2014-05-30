#include "TranspositionTableData.h"

namespace engine {

	TranspositionTableData::TranspositionTableData(int score) {
		_score = score;
		_maxBestMove = nullptr;
		_minBestMove = nullptr;
	}


	TranspositionTableData::~TranspositionTableData(void) {
		delete _maxBestMove;
		delete _minBestMove;
	}

	
	Move* TranspositionTableData::GetMaxBestMove() {
		return _maxBestMove;
	}
	Move* TranspositionTableData::GetMinBestMove() {
		return _minBestMove;
	}

	void TranspositionTableData::SetMaxBestMove(Move* move) {
		delete _maxBestMove;
		_maxBestMove = move;
	}

	void TranspositionTableData::SetMinBestMove(Move* move) {
		delete _minBestMove;
		_minBestMove = move;
	}

	int TranspositionTableData::GetScore() {
		return _score;
	}
}
