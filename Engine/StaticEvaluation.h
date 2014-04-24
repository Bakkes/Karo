#pragma once
#include "IStaticEvaluation.h"

namespace engine {
	class StaticEvaluation : public IStaticEvaluation
	{
	public:
		StaticEvaluation(void);
		~StaticEvaluation(void);
		int Eval(IBoard*, Players);
	private:
		int flippedValue;
		int blockedTileValue;
		int cornerValue;
		int neighborValue;
		int lineValue;
	};
}
