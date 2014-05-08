#include "ComputerPlayerAB.h"
#include "ComputerPlayerUtils.h"
#include <Windows.h>
#include <sstream>

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

	void printInteger(int i) {

		stringstream string;
		string << i;
		OutputDebugString(string.str().c_str());
	}

	void printPlayer(Players player) {
		if (player == Max) {
			OutputDebugStringW(L"Max");
		} else {
			OutputDebugStringW(L"Min");
		}
	}

	EvalResult& ComputerPlayerAB::MinimaxStep(Players player, int depth, EvalResult& result) {
		OutputDebugStringW(L"MinimaxStep(");
		printPlayer(player);
		OutputDebugStringW(L", ");
		printInteger(depth);
		OutputDebugStringW(L", bestForMax=");
		printInteger(result.GetBestForMax());
		OutputDebugStringW(L", bestForMin=");
		printInteger(result.GetBestForMin());
		OutputDebugStringW(L")\n");

		std::vector<Move>* possibleMoves = _board->GetLegalMoves(player);
		for (auto it = possibleMoves->begin(); it != possibleMoves->end(); ++it) {
			Move move = (*it);
			_board->ExecuteMove(&move, player);
			EvalResult score = GetScore(player, move, depth, result);
			_board->ExecuteMove(&ComputerPlayerUtils::InvertMove(move), player);

			OutputDebugStringW(L"MoveCompare: Player=");
			printPlayer(player);
			OutputDebugStringW(L", Score=");
			printInteger(score.GetScore());
			OutputDebugStringW(L", bestForMax=");
			printInteger(result.GetBestForMax());
			OutputDebugStringW(L", bestForMin=");
			printInteger(result.GetBestForMin());
			OutputDebugStringW(L"\n");

			if (player == Max) {
				if (score.GetScore() <= result.GetBestForMin() && result.GetBestForMin() != INT_MAX) {
					// Cut off
					OutputDebugStringW(L"Max Node Cut off\n");
					SwapMinMaxInResult(result);
					break;
				} else if (score.GetScore() < result.GetBestForMax()) {
					result.SetBestForMax(score.GetScore());
					result.SetMove(score.GetMove());
					result.SetScore(score.GetScore());
				}
			} else  if (player == Min)  {
				if (score.GetScore() <= result.GetBestForMax() && result.GetBestForMax() != INT_MIN) {
					// Cut off
					OutputDebugStringW(L"Min Node Cut off\n");
					SwapMinMaxInResult(result);
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

			OutputDebugStringW(L"RET MinimaxStep(");
			if (player == Max) {
				OutputDebugStringW(L"Max");
			} else {
				OutputDebugStringW(L"Min");
			}
			OutputDebugStringW(L", ");
			printInteger(depth);
			OutputDebugStringW(L", bestForMax=");
			printInteger(result.GetBestForMax());
			OutputDebugStringW(L", bestForMin=");
			printInteger(result.GetBestForMin());
			OutputDebugStringW(L")\n");


			// Propogade the values up tree -> So swap them
			SwapMinMaxInResult(result);
			
			OutputDebugStringW(L"Propogading Score\n");
			return score;
		} else {
			// We can't go deeper, evaluate the board
			EvalResult score(result.GetBestForMax(), result.GetBestForMin());
			score.SetMove(move);
			score.SetScore(_evaluator->Eval(_board, player));
			OutputDebugStringW(L"Eval Score: ");
			printInteger(score.GetScore());
			OutputDebugStringW(L"\n");
			
			return score;
		}

	}

	void ComputerPlayerAB::SwapMinMaxInResult(EvalResult& er) {
			int oldMax = er.GetBestForMax();
			int oldMin = er.GetBestForMin();
			if (oldMax == INT_MIN) {
				oldMax = INT_MAX;
			}
			if (oldMin == INT_MAX) {
				oldMin = INT_MIN;
			}
			er.SetBestForMax(oldMin);
			er.SetBestForMin(oldMax);
	}

	void ComputerPlayerAB::SetEvaluator(IStaticEvaluation* evaluator) {
		delete _evaluator;
		_evaluator = evaluator;
	}

}
