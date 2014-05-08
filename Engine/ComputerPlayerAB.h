#pragma once
#include <stack>

#include "EvalResult.h"
#include "IComputerPlayer.h"
#include "IStaticEvaluation.h"
#include "Players.h"

namespace engine {

	class ENGINE_API ComputerPlayerAB : public IComputerPlayer {
	public:
		ComputerPlayerAB(IBoard* board, int maxDepth);
		~ComputerPlayerAB() override;
		virtual Move GetBestMove(Players player) override;
		void SetEvaluator(IStaticEvaluation* evaluator);

	private:
		// The Static Evaluation function which will evaluate the board
		IStaticEvaluation* _evaluator;
		// The maximum depth of the minimax search
		int _maxDepth;
		// The unsafe board which is the playground of the AI
		IBoard* _board;
		// Executes a single step from the Minimax algorithm
		EvalResult MinimaxStep(Players player, int depth, EvalResult result);
		// Gets the score for the current phase, it either iterates deeper and takes that result
		// or executes the static evaluation and uses that result.
		EvalResult GetScore(Players player, Move move, int depth, EvalResult result);
	};

}
