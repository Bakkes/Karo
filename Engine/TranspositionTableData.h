#pragma once
#include "Move.h"

namespace engine{
	class ENGINE_API TranspositionTableData
	{
	private:
		int _score;
		Move* _bestMove;
	public:
		TranspositionTableData(int score, Move* bestMove);
		~TranspositionTableData(void);
		Move* GetBestMove();

		int GetScore();
	};
}
