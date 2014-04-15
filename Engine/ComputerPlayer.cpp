#include "ComputerPlayer.h"

namespace engine {

	ComputerPlayer::ComputerPlayer(void) {
	}

	ComputerPlayer::~ComputerPlayer(void) {
	}

	int ComputerPlayer::Eval() {
		return rand();
	}

	Move ComputerPlayer::GetBestMove() {
		return Move(MoveType::JUMP, 0, 1, MoveDirection::NORTH, -1);
	}
}
