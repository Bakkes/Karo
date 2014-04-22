#pragma once

#include "IStaticEvaluation.h"

namespace engine {

	class ENGINE_API RandStaticEval : public IStaticEvaluation {
	public:
		RandStaticEval();
		~RandStaticEval();

		int Eval(IBoard* board, Players player) override;

		int GetLowestScore();
		int GetHighestScore();

	private:
		int _lowestScore;
		int _highestScore;
	};
}
