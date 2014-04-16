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
		return Move(INSERT, Vector2D(3,4));
	}

	Move ComputerPlayer::MinimaxStep(Players player, int depth) {
		std::vector<Move>* possibleMoves = _board->GetLegalMoves(player);
		for (auto move = possibleMoves->begin(); move != possibleMoves->end(); move++) {
			_board->ExecuteMove(&(*move), player);

			_evaluator->Eval(_board, player);

			_board->ExecuteMove(&(*move), player);
		}
		delete possibleMoves;

		return Move(INSERT, Vector2D(3,4));
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
