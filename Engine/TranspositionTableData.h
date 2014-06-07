#pragma once
#include "Move.h"
#include "Players.h"

namespace engine{
	class ENGINE_API TranspositionTableData
	{
	private:
		int _score;
		int _depth;
		Move* _bestMoveMin;
		Move* _bestMoveMax;
	public:
		TranspositionTableData(int score, int depth);
		~TranspositionTableData(void);

		void SetBestMove(Players player, Move* move);

		Move* GetBestMove(Players player);
		int GetScore();
		int GetDepth();
	};
}
