#include "AI.h"

namespace engine{

	AI::AI(IBoard* board, int maxDepth)
	{
		_board = board;
		_maxDepth = maxDepth;
		_evaluator = nullptr;
		_extensions = new vector<AIExtension*>();
		_staticEvalCallCount = 0;
		_nodesSeen = 0;
	}


	AI::~AI(void)
	{
		delete _evaluator;
		_evaluator = nullptr;
		for_each(_extensions->begin(), _extensions->end(),[](AIExtension* extension) -> void{
			delete extension;
		});
		delete _extensions;
		_extensions = nullptr;
	}

	Move AI::GetBestMove(Players player){
		for_each(_extensions->begin(), _extensions->end(),[this](AIExtension* extension) -> void{
			extension->Start(_maxDepth, _board, _evaluator);
		});
		EvalResult result = MinimaxStep(player, 0, EvalResult(INT_MIN, INT_MAX));
		for_each(_extensions->begin(), _extensions->end(), [](AIExtension* extension) -> void{
			extension->End();
		});
		return result.GetMove();
	}

	void AI::AddExtension(AIExtension* extension){
		_extensions->push_back(extension);
	}

	void AI::SetEvaluator(IStaticEvaluation* evaluator) {
		_evaluator = evaluator;
	}

	EvalResult AI::MinimaxStep(Players player, int depth, EvalResult result){
		// allow extensions to set te result
		for_each(_extensions->begin(), _extensions->end(), [&](AIExtension* extension) -> void{
			extension->Step(player, depth, result);
		});

		std::vector<Move> possibleMoves = _board->GetLegalMoves(player);

		// allow extensoins to do some move ordering
		for_each(_extensions->begin(), _extensions->end(), [&depth, &possibleMoves, &player](AIExtension* extension) -> void{
			extension->UpdateMoves(possibleMoves, player, depth);
		});

		for (auto it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {
			Move move = (*it);

			_board->ExecuteMove(move, player);
			++_nodesSeen;

			for_each(_extensions->begin(), _extensions->end(), [&move](AIExtension* extension) -> void{
				// Executed move
				extension->OnExecuteMove(move);
			});


			EvalResult currentResult = NextStep(player, move, depth, result);

			_board->UndoMove(move, player);
			for_each(_extensions->begin(), _extensions->end(), [&move, &player](AIExtension* extension) -> void{
				// Undone move
				extension->OnUndoMove(move, player);
			});

			// allows for pruning
			for(auto extension = _extensions->begin(); extension != _extensions->end(); ++extension){
				if(!(*extension)->ShouldContinue(currentResult, result, player)){
					return result;
				}
			}
		}

		// Register board
		for(auto extension = _extensions->begin(); extension != _extensions->end(); ++extension) {
			(*extension)->RegisterBoard(result, depth, player);
		}

		return result;
	}
	EvalResult AI::NextStep(Players player, Move move, int depth, EvalResult result) {
		// If one of the players has won, return an EvalResult with huge +/- numbers.
		if (ComputerPlayerUtils::IsWinningState(_board, Max)) {
			EvalResult _result;
			_result.SetScore(INT_MAX - depth);
			_result.SetMove(move);
			return _result;
		} else if (ComputerPlayerUtils::IsWinningState(_board, Min)) {
			EvalResult _result;
			_result.SetScore(INT_MIN + depth);
			_result.SetMove(move);
			return _result;
		}

		if (depth + 1 < _maxDepth) {
			// We are allowed to go deeper, take the result of the next step
			EvalResult _result = MinimaxStep(ComputerPlayerUtils::InvertPlayer(player), depth + 1, result);
			_result.SetMove(move);
			return _result;
		}

		// We can't go deeper, evaluate the board
		EvalResult score(result.GetBestForMax(), result.GetBestForMin());
		score.SetScore(_evaluator->Eval(_board, player));
		score.SetMove(move);

		++_staticEvalCallCount;

		return score;
	}

	int AI::GetStaticEvalCallCount() {
		return _staticEvalCallCount;
	}

	int AI::GetNodesSeenCount() {
		return _nodesSeen;
	}
}