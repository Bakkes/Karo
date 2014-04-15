#pragma once
#include "IComputerPlayer.h"
#include "IStaticEvaluation.h"

namespace engine {

	class ENGINE_API ComputerPlayer : public IComputerPlayer {
	public:
		ComputerPlayer();
		~ComputerPlayer() override;
		virtual int Eval() override;
		virtual Move GetBestMove() override;

	private:
		// The Static Evaluation function which will evaluate the board
		IStaticEvaluation evalulator;
	};
}
