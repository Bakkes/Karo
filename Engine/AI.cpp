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
		for_each(_extensions.begin(), _extensions.end(),[this](AIExtension extension) -> void{
			extension.Start(_maxDepth);
		});
		EvalResult result = MinimaxStep(player, _maxDepth, EvalResult(INT_MIN, INT_MAX));
		for_each(_extensions.begin(), _extensions.end(), [](AIExtension extension) -> void{
			extension.End();
		});
		return result.GetMove();
	}
	void AI::AddExtension(AIExtension extension){
		_extensions.push_back(extension);
	}
	void AI::SetEvaluator(IStaticEvaluation* evaluator) {
		_evaluator = evaluator;
	}
	EvalResult AI::MinimaxStep(Players player, int depth, EvalResult result){
		// allow extensions to set te result
		for_each(_extensions.begin(), _extensions.end(), [&](AIExtension extension) -> void{
			extension.Step(player, depth, result);
		});

		std::vector<Move> possibleMoves = _board->GetLegalMoves(player);

		// allow extensoins to do some move ordering
		for_each(_extensions.begin(), _extensions.end(), [&depth, &possibleMoves](AIExtension extension) -> void{
			extension.UpdateMoves(depth, possibleMoves);
		});

		for (auto it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {

			Move move = (*it);
			_board->ExecuteMove(move, player);
			EvalResult currentResult = NextStep(player, move, depth, result);
			_board->UndoMove(move, player);


			// allows for pruning
			for(auto extension = _extensions.begin(); extension != _extensions.end(); ++extension){
				if(!extension->ShouldContinue(currentResult, result, player)){
					return result;
				}
			}
		}
		return result;
	}
	EvalResult AI::NextStep(Players player, Move move, int depth, EvalResult result) {
		if (depth + 1 < _maxDepth) {
			// We are allowed to go deeper, take the result of the next step
			return MinimaxStep(ComputerPlayerUtils::InvertPlayer(player), depth + 1, result);
		}

		// We can't go deeper, evaluate the board
		EvalResult score(result.GetBestForMax(), result.GetBestForMin());
		score.SetMove(move);
		score.SetScore(_evaluator->Eval(_board, player));
		return score;
	}
}