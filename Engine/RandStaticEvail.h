#pragma once

#include "IStaticEvaluation.h"

namespace engine {

	class RandStaticEvail : public IStaticEvaluation {
	public:
		RandStaticEvail();
		~RandStaticEvail();

		int Eval(IBoard* board, Players player) override;
	};
}
