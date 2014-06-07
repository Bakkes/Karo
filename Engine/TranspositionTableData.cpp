#include "TranspositionTableData.h"

namespace engine {

	TranspositionTableData::TranspositionTableData(int score, int depth) {
		_score = score;
		_depth = depth;
	}


	TranspositionTableData::~TranspositionTableData(void) {
		delete _bestMoveMax;
		delete _bestMoveMin;
	}

	void TranspositionTableData::SetBestMove(Players player, Move* move) {
		if (player == Max) {
			delete _bestMoveMax;
			_bestMoveMax = move;
		} else if (player == Min) {
			delete _bestMoveMin;
			_bestMoveMin = move;
		}
	}
	
	Move* TranspositionTableData::GetBestMove(Players player) {
		if (player == Max)
			return _bestMoveMax;
		if (player == Min)
			return _bestMoveMin;

		return nullptr;
	}

	int TranspositionTableData::GetScore() {
		return _score;
	}

	int TranspositionTableData::GetDepth() {
		return _depth;
	}
}
