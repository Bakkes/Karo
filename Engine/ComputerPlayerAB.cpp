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
		return MinimaxStep(player, 0, INT_MAX, INT_MIN).GetMove();
	}

	EvalResult ComputerPlayerAB::MinimaxStep(Players player, int depth, int bestForMax, int bestForMin) {
		EvalResult result(bestForMax, bestForMin);
		std::vector<Move>* possibleMoves = _board->GetLegalMoves(player);
		for (auto it = possibleMoves->begin(); it != possibleMoves->end(); ++it) {
			Move move = (*it);
			_board->ExecuteMove(&move, player);

			EvalResult score;
			if (depth + 1 <= _maxDepth) {
				// We are allowed to go deeper, take the result of the next step
				score = MinimaxStep(ComputerPlayerUtils::InvertPlayer(player), depth + 1, bestForMax, bestForMin);
				// Propogade the values up tree -> So swap them
				int temp = score.GetBestForMax();
				score.SetBestForMax(score.GetBestForMin());
				score.SetBestForMin(temp);
			} else {
				// We can't go deeper, evaluate the board
				score.SetMove(move);
				score.SetScore(_evaluator->Eval(_board, player));
			}

			if (!result.IsSet() || // We don't have a result yet, copy it
				(player == Max && score.GetScore() < bestForMax) || // Result is better if we are the max player
				(player == Min && score.GetScore() > bestForMin)) { // Result is better if we are the min player

				if (player == Max) { // Modify the bestForMax value for the max player
					if (score.GetScore() > bestForMax) { // The ranges no longer overlap, prune it
						break;
					}
					bestForMin = score.GetScore();
					result.SetBestForMin(bestForMin);
				} else { // Modify the bestForMin value for the min player
					if (bestForMin > score.GetScore()) { // The ranges no longer overlap, prune it
						break;
					}
					bestForMax = score.GetScore();
					result.SetBestForMax(bestForMax);
				}

				// Set the move and score to the result which is "the best move" from this node
				result.SetMove(score.GetMove());
				result.SetScore(score.GetScore());
			}
			
			_board->ExecuteMove(&ComputerPlayerUtils::InvertMove(move), player);
		}
		delete possibleMoves;

		return result;
	}

	void ComputerPlayerAB::SetEvaluator(IStaticEvaluation* evaluator) {
		delete _evaluator;
		_evaluator = evaluator;
	}

}
