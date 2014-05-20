#include "AI.h"

namespace engine{

	AI::AI(IBoard* board, int maxDepth)
	{
		_board = board;
		_maxDepth = maxDepth;
		_evaluator = nullptr;
	}


	AI::~AI(void)
	{
	}

	Move AI::GetBestMove(Players player){
		for_each(_extensions.begin(), _extensions.end(), [](AIExtension extension) -> void{
			extension.Start();
		});
		MinimaxStep(player, _maxDepth, EvalResult(INT_MIN, INT_MAX));
		for_each(_extensions.begin(), _extensions.end(), [](AIExtension extension) -> void{
			extension.End();
		});
	}
	void AI::AddExtension(AIExtension extension){
		_extensions.push_back(extension);
	}
	void AI::SetEvaluator(IStaticEvaluation* evaluator) {
		_evaluator = evaluator;
	}
	EvalResult AI::MinimaxStep(Players player, int depth, EvalResult result){
		// allow extensions to set te result
		for_each(_extensions.begin(), _extensions.end(), [&result](AIExtension extension) -> void{
			extension.Step(result);
		});

		std::vector<Move> possibleMoves = _board->GetLegalMoves(player);

		// allow extensoins to do some move ordering
		for_each(_extensions.begin(), _extensions.end(), [&possibleMoves](AIExtension extension) -> void{
			extension.UpdateMoves(possibleMoves);
		});

		for (auto it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {

			Move move = (*it);
			_board->ExecuteMove(move, player);
			NextStep(player, move, depth, result);
			_board->UndoMove(move, player);

			bool shouldContinue = true;

			// allow extensions to figure out pruning
			for_each(_extensions.begin(), _extensions.end(), [&](AIExtension extension) -> void{
				shouldContinue = shouldContinue && extension.ShouldContinue(result, player);
			});
			if(!shouldContinue){
				break;
			}
		}
		return result;
	}
	void AI::NextStep(Players player, Move move, int depth, EvalResult& result) {
		if (depth + 1 < _maxDepth) {
			// We are allowed to go deeper, take the result of the next step
			MinimaxStep(ComputerPlayerUtils::InvertPlayer(player), depth + 1, result);
			return;
		}

		// We can't go deeper, evaluate the board
		EvalResult score(result.GetBestForMax(), result.GetBestForMin());
		score.SetMove(move);
		score.SetScore(_evaluator->Eval(_board, player));
	}
}