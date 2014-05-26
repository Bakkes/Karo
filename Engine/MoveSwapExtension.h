#pragma once
#include "AIExtension.h"
namespace engine{
	// an instance of this class alows an AI to prefer moves that are marked as
	// killer moves in other branches of the minmax tree of the same depth
	class MoveSwapExtension : public AIExtension
	{
	public:
		MoveSwapExtension(void);
		~MoveSwapExtension(void);
		void Start(const int& maxDepth, IBoard* board, IStaticEvaluation* evaluation) override;
		// notify the exntension taht minmax ends
		void End() override;
		// allows extension to do move ordering
		void UpdateMoves(const int& depth, std::vector<Move>& moves) override;
		bool ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player) override;
	private:

		bool ShouldSwap();
		EvalResult* _killerMoves;
	};

}