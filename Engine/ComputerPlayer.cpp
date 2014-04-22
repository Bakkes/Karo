#include "ComputerPlayer.h"

namespace engine {

	ComputerPlayer::ComputerPlayer(IBoard* board, int maxDepth) {
		_board = board;
		_maxDepth = maxDepth;
		_evaluator = nullptr;
		_moveHistory = new std::stack<Move*>();
	}

	ComputerPlayer::~ComputerPlayer() {
		delete _evaluator;
		_evaluator = nullptr;
		delete _moveHistory;
		_moveHistory = nullptr;
	}

	Move ComputerPlayer::GetBestMove(Players player) {
		return MinimaxStep(player, 0, INT_MAX, INT_MIN).GetMove();
	}

	EvalResult ComputerPlayer::MinimaxStep(Players player, int depth, int bestForMax, int bestForMin) {
		EvalResult result;
		std::vector<Move>* possibleMoves = _board->GetLegalMoves(player);
		for (auto it = possibleMoves->begin(); it != possibleMoves->end(); --it) {
			Move move = (*it);
			_board->ExecuteMove(&move, player);

			EvalResult score;
			if (depth + 1 <= _maxDepth) {
				// We are allowed to go deeper, take the result of the next step
				score = MinimaxStep(InvertPlayer(player), depth + 1, bestForMax, bestForMin);
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

				if (player == Max) { // Modify the bestForMax) value for the max player
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
			
			_board->ExecuteMove(&InvertMove(move), player);
		}
		delete possibleMoves;

		return result;
	}

	void ComputerPlayer::SetEvaluator(IStaticEvaluation* evaluator) {
		_evaluator = evaluator;
	}

	Move InvertMove(Move move) {
		switch (move.GetMoveType()) {
		case INSERT:
			return Move(DELETE, move.GetToCell());
		case MOVE: {
			if (move.HasUsedCell()) {
				return Move(MOVE, move.GetUsedCell(), move.GetFromCell(), move.GetToCell());
			} else {
				return Move(MOVE, move.GetToCell(), move.GetFromCell());
			}
		}
		case JUMP: {
			if (move.HasUsedCell()) {
				return Move(JUMP, move.GetUsedCell(), move.GetFromCell(), move.GetToCell());
			} else {
				return Move(JUMP, move.GetToCell(), move.GetFromCell());
			}
		}
		}

		return Move(INSERT, Vector2D(-1,-1));
	}

	Players InvertPlayer(Players player) {
		if (player == Players::Min) {
			return Players::Max;
		}
		return Players::Min;
	}
}
