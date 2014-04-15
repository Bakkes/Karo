#pragma once
#include "Move.h"

namespace engine {
	class IComputerPlayer {
	public:
		virtual ~IComputerPlayer() {
		}

		virtual Move GetBestMove() = 0;
	};
}