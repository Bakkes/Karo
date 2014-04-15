#include "ComputerPlayer.h"

namespace engine {

	ComputerPlayer::ComputerPlayer(IBoard* board, int maxDepth) {
		_maxDepth = maxDepth;
	}

	ComputerPlayer::~ComputerPlayer() {
	}

	Move ComputerPlayer::GetBestMove() {
		return Move(MoveType::JUMP, 0, 1, MoveDirection::NORTH, -1);
	}

	Move ComputerPlayer::MinimaxStep(Players player, int depth) {
		std::vector<Move>* possibleMoves = _board->GetLegalMoves();
		for (auto move = possibleMoves->begin(); move != possibleMoves->end(); move++) {
			_board->ExecuteMove(&(*move));

			_evaluator.Eval(_board, player);

			_board->ExecuteMove(&(*move));
		}
		delete possibleMoves;
	}

	Move InvertMove(Move move) {

	}

	Players InvertPlayer(Players player) {
		if (player == Players::Min)
			return Players::Max;
		return Players::Min;
	}
}
