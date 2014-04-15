#include "ComputerPlayer.h"

namespace engine {

	ComputerPlayer::ComputerPlayer(IBoard* board, int maxDepth) {
		_maxDepth = maxDepth;
		_evaluator = NULL;
	}

	ComputerPlayer::~ComputerPlayer() {
		if (_evaluator != NULL)
			delete _evaluator;
	}

	Move ComputerPlayer::GetBestMove(Players player) {
		return Move(MoveType::JUMP, 0, 1, MoveDirection::NORTH, -1);
	}

	Move ComputerPlayer::MinimaxStep(Players player, int depth) {
		std::vector<Move>* possibleMoves = _board->GetLegalMoves();
		for (auto move = possibleMoves->begin(); move != possibleMoves->end(); move++) {
			_board->ExecuteMove(&(*move));

			_evaluator->Eval(_board, player);

			_board->ExecuteMove(&(*move));
		}
		delete possibleMoves;

		return Move(MoveType::DELETE, -1, -1, MoveDirection::NONE, -1); 
	}

	//Move::Move(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile) {

	Move InvertMove(Move move) {
		switch (move.GetMoveType()) {
		case MoveType::INSERT:
			return Move(MoveType::DELETE, -1, move.GetToTile(), MoveDirection::NONE, -1);
		case MoveType::JUMP:
			if (move.GetEmptyTile() != -1) {
				// Grabbed a tile, put it back and undo the jump
				// TODO Fix this function once the board API is final
				return Move(MoveType::DELETE, -1, -1, MoveDirection::NONE, -1); 
			} else {
				// Normal jump
				return Move(MoveType::JUMP, move.GetToTile(), move.GetFromTile(), MoveDirection::NONE, -1);
			}
		case MoveType::MOVE:
			if (move.GetEmptyTile() != -1) {
				// Grabbed a tile, put it back and undo the move
				// TODO Fix this function once the board API is final
				return Move(MoveType::DELETE, -1, -1, MoveDirection::NONE, -1); 
			} else {
				// Normal move
				return Move(MoveType::MOVE, move.GetToTile(), move.GetFromTile(), MoveDirection::NONE, -1);
			}
		}
		return Move(MoveType::DELETE, -1, -1, MoveDirection::NONE, -1); 
	}

	Players InvertPlayer(Players player) {
		if (player == Players::Min)
			return Players::Max;
		return Players::Min;
	}
}
