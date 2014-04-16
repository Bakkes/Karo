#pragma once

#include "IStaticEvaluation.h"

namespace engine {

	class ENGINE_API RandStaticEvail : public IStaticEvaluation {
	public:
		RandStaticEvail();
		~RandStaticEvail();

		int Eval(IBoard* board, Players player) override;
	};
}
