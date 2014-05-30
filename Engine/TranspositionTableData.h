#pragma once
#include "Move.h"

namespace engine{
	class ENGINE_API TranspositionTableData
	{
	private:
		int _score;
		Move* _maxBestMove;
		Move* _minBestMove;
	public:
		TranspositionTableData(int score);
		~TranspositionTableData(void);
		Move* GetMaxBestMove();
		Move* GetMinBestMove();

		void SetMaxBestMove(Move* move);
		void SetMinBestMove(Move* move);

		int GetScore();
	};
}
