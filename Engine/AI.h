#pragma once
#include "IComputerPlayer.h"
#include "AIExtension.h"
#include "EvalResult.h"
#include "IStaticEvaluation.h"
#include "ComputerPlayerUtils.h"
#include <algorithm>
#include <vector>
namespace engine {
	class ENGINE_API AI : public IComputerPlayer
	{
	public:
		AI(IBoard* board, int maxDepth);
		~AI(void);
		Move GetBestMove(Players player) override;
		// add the extensions to this ai, when the ai is gone the extension
		// will also be cleaned
		void AddExtension(AIExtension*);
		void SetEvaluator(IStaticEvaluation* evaluator);

		int GetStaticEvalCallCount();
		int GetNodesSeenCount();

	private:
		std::vector<AIExtension*>* _extensions;
		// The Static Evaluation function which will evaluate the board
		IStaticEvaluation* _evaluator;
		// The maximum depth of the minimax search
		int _maxDepth;
		// The unsafe board which is the playground of the AI
		IBoard* _board;
		// Executes a single step from the Minimax algorithm
		EvalResult MinimaxStep(Players player, int depth, EvalResult);
		EvalResult NextStep(Players player, Move move, int depth, EvalResult);

		int _staticEvalCallCount;
		int _nodesSeen;
	};
}
