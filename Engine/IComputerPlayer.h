#pragma once
#include "Move.h"
#include "Players.h"

namespace engine {
	class ENGINE_API IComputerPlayer {
	public:
		virtual ~IComputerPlayer() {
		}

		// Creates the best move for the given player
		virtual Move GetBestMove(Players player) = 0;
	};
}