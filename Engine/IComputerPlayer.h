#pragma once
#include "Move.h"

namespace Engine {
	class IComputerPlayer {
	public:
		virtual ~IComputerPlayer(void);
		virtual int Eval() = 0;
		virtual Move GetBestMove() = 0;
	};
}