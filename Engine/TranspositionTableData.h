#pragma once
#include "Move.h"

namespace engine{
	class ENGINE_API TranspositionTableData
	{
	private:
		int _score;
		int _depth;
		Move* _bestMove;
	public:
		TranspositionTableData(int score, Move* bestMove, int depth);
		~TranspositionTableData(void);
		Move* GetBestMove();

		int GetScore();
		int GetDepth();
	};
}
