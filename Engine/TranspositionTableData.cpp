#include "TranspositionTableData.h"

namespace engine{
	TranspositionTableData::TranspositionTableData(int score, Move* maxBestMove, Move* minBestMove)
	{
		_score = score;
		_maxBestMove = maxBestMove;
		_minBestMove = minBestMove;
	}


	TranspositionTableData::~TranspositionTableData(void)
	{
		delete _maxBestMove;
		delete _minBestMove;
	}

	
	Move* TranspositionTableData::GetMaxBestMove()
	{
		return _maxBestMove;
	}
	Move* TranspositionTableData::GetMinBestMove()
	{
		return _minBestMove;
	}

	int TranspositionTableData::GetScore()
	{
		return _score;
	}
}
