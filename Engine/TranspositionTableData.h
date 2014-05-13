#pragma once
#include "Move.h"

namespace engine{
	class TranspositionTableData
	{
	private:
		int _score;
		Move* _maxBestMove;
		Move* _minBestMove;
	public:
		TranspositionTableData(int score, Move* maxBestMove, Move* minBestMove);
		~TranspositionTableData(void);
		Move* GetMaxBestMove();
		Move* GetMinBestMove();
		int GetScore();
	};
}
