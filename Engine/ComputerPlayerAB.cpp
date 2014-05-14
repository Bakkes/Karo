#include "ComputerPlayerAB.h"
#include "ComputerPlayerUtils.h"

namespace engine {
	/*
	 * Computer AI with the Alpha Beta Pruning
	 */

	ComputerPlayerAB::ComputerPlayerAB(IBoard* board, int maxDepth) {
		_board = board;
		_maxDepth = maxDepth;
		_evaluator = nullptr;
	}

	ComputerPlayerAB::~ComputerPlayerAB() {
		delete _evaluator;
		_evaluator = nullptr;
	}

	Move ComputerPlayerAB::GetBestMove(Players player) {
		return MinimaxStep(player, 0, EvalResult(INT_MIN, INT_MAX)).GetMove();
	}

	EvalResult ComputerPlayerAB::MinimaxStep(Players player, int depth, EvalResult result) {
		if (player == Max) {
			result.SetScore(INT_MIN);
		} else {
			result.SetScore(INT_MAX);
		}

		std::vector<Move> possibleMoves = _board->GetLegalMoves(player);
		for (auto it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {
			Move move = (*it);
			_board->ExecuteMove(move, player);
			EvalResult score = GetScore(player, move, depth, result);
			_board->UndoMove(move, player);

			if (player == Max) {
				if (score.GetScore() > result.GetScore()) {
					result.SetScore(score.GetScore());
				}

				if (score.GetScore() >= result.GetBestForMin() && result.GetBestForMin() != INT_MAX) {
					// Cut off
					break;
				} else if (score.GetScore() > result.GetBestForMax()) {
					result.SetBestForMax(score.GetScore());
					result.SetMove(score.GetMove());
				}
			} else  if (player == Min)  {
				if (score.GetScore() < result.GetScore()) {
					result.SetScore(score.GetScore());
				}

				if (score.GetScore() <= result.GetBestForMax() && result.GetBestForMax() != INT_MIN) {
					// Cut off
					break;
				} else if (score.GetScore() < result.GetBestForMin()) {
					result.SetBestForMin(score.GetScore());
					result.SetMove(score.GetMove());
				}
			}

		}
		

		return result;
	}

	EvalResult ComputerPlayerAB::GetScore(Players player, Move move, int depth, EvalResult result) {
		if (depth + 1 < _maxDepth && !ComputerPlayerUtils::IsWinningState(_board)) {
			// We are allowed to go deeper, take the result of the next step
			return MinimaxStep(ComputerPlayerUtils::InvertPlayer(player), depth + 1, result);
		}

		// We can't go deeper, evaluate the board
		EvalResult score(result.GetBestForMax(), result.GetBestForMin());
		score.SetMove(move);
		score.SetScore(_evaluator->Eval(_board, player));
		
		return score;
	}

	void ComputerPlayerAB::SetEvaluator(IStaticEvaluation* evaluator) {
		delete _evaluator;
		_evaluator = evaluator;
	}

}
