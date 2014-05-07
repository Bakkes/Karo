#include "ComputerPlayerAB.h"
#include "ComputerPlayerUtils.h"
#include <Windows.h>

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

	EvalResult& ComputerPlayerAB::MinimaxStep(Players player, int depth, EvalResult& result) {
		std::vector<Move>* possibleMoves = _board->GetLegalMoves(player);
		for (auto it = possibleMoves->begin(); it != possibleMoves->end(); ++it) {
			Move move = (*it);
			_board->ExecuteMove(&move, player);
			EvalResult score = GetScore(player, move, depth, result);
			_board->ExecuteMove(&ComputerPlayerUtils::InvertMove(move), player);

			if (player == Max) {
				if (score.GetScore() <= result.GetBestForMax() && result.GetBestForMax() != INT_MIN) {
					// Cut off
					OutputDebugStringW(L"Max Node Cut off\n");
					break;
				} else if (score.GetScore() < result.GetBestForMax()) {
					result.SetBestForMax(score.GetScore());
					result.SetMove(score.GetMove());
					result.SetScore(score.GetScore());
				}
			} else  if (player == Min)  {
				if (score.GetScore() <= result.GetBestForMin() && result.GetBestForMin() != INT_MAX) {
					// Cut off
					OutputDebugStringW(L"Min Node Cut off\n");
					break;
				} else if (score.GetScore() < result.GetBestForMin()) {
					result.SetBestForMin(score.GetScore());
					result.SetMove(score.GetMove());
					result.SetScore(score.GetScore());
				}
			}

		}
		delete possibleMoves;

		return result;
	}

	EvalResult ComputerPlayerAB::GetScore(Players player, Move move, int depth, EvalResult& result) {
		if (depth + 1 < _maxDepth) {
			OutputDebugStringW(L"Going Down\n");

			// We are allowed to go deeper, take the result of the next step
			EvalResult score = MinimaxStep(ComputerPlayerUtils::InvertPlayer(player), depth + 1, result);

			// Propogade the values up tree -> So swap them
			int temp = score.GetBestForMax();
			score.SetBestForMax(score.GetBestForMin());
			score.SetBestForMin(temp);

			OutputDebugStringW(L"Propogading Score\n");
			return score;
		} else {
			// We can't go deeper, evaluate the board
			EvalResult score(result.GetBestForMax(), result.GetBestForMin());
			score.SetMove(move);
			score.SetScore(_evaluator->Eval(_board, player));
			OutputDebugStringW(L"Eval Score\n");
			
			return score;
		}

	}

	void ComputerPlayerAB::SetEvaluator(IStaticEvaluation* evaluator) {
		delete _evaluator;
		_evaluator = evaluator;
	}

}
