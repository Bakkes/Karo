#include "ComputerPlayer.h"

namespace engine {

	ComputerPlayer::ComputerPlayer(IBoard* board, int maxDepth) {
		_maxDepth = maxDepth;
		_evaluator = NULL;
		_moveHistory = new std::stack<Move*>();
	}

	ComputerPlayer::~ComputerPlayer() {
		if (_evaluator != NULL)
			delete _evaluator;
		delete _moveHistory;
	}

	Move ComputerPlayer::GetBestMove(Players player) {
		return MinimaxStep(player, 0).GetMove();
	}

	EvalResult ComputerPlayer::MinimaxStep(Players player, int depth) {
		EvalResult result;
		std::vector<Move>* possibleMoves = _board->GetLegalMoves(player);
		for (auto it = possibleMoves->begin(); it != possibleMoves->end(); --it) {
			Move move = (*it);
			_board->ExecuteMove(&move, player);

			EvalResult score;
			if (depth + 1 <= _maxDepth) {
				// We are allowed to go deeper, take the result of the next step
				score = MinimaxStep(InvertPlayer(player), depth + 1);
			} else {
				// We can't go deeper, evaluate the board
				score.SetMove(move);
				score.SetScore(_evaluator->Eval(_board, player));
			}

			if (!result.IsSet() || // We don't have a result yet, copy it
				(player == Max && result.GetScore() < score.GetScore()) || // Result is better if we are the max player
				(player == Min && result.GetScore() > score.GetScore())) { // Result is better if we are the min player

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
			return Move(DELETE, move.GetToTile());
		case MOVE: {
			if (move.HasUsedTile()) {
				return Move(MOVE, move.GetUsedTile(), move.GetFromTile(), move.GetToTile());
			} else {
				return Move(MOVE, move.GetToTile(), move.GetFromTile());
			}
		}
		case JUMP: {
			if (move.HasUsedTile()) {
				return Move(JUMP, move.GetUsedTile(), move.GetFromTile(), move.GetToTile());
			} else {
				return Move(JUMP, move.GetToTile(), move.GetFromTile());
			}
		}
		}

		return Move(INSERT, Vector2D(-1,-1));
	}

	Players InvertPlayer(Players player) {
		if (player == Players::Min)
			return Players::Max;
		return Players::Min;
	}
}
