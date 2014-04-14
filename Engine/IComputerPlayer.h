#pragma once
#include "Move.h"

namespace engine {
	class IComputerPlayer {
	public:
		virtual ~IComputerPlayer() {
		}
		virtual int Eval() = 0;
		virtual Move GetBestMove() = 0;
	};
}