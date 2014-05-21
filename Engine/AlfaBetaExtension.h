#pragma once
#include "AIExtension.h"
namespace engine{
	class AlfaBetaExtension : AIExtension
	{
	public:
		AlfaBetaExtension(void);
		~AlfaBetaExtension(void);
		void Step(const Players& player, const int& currentDepth, EvalResult&) override;
		bool ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player) override;
	};

}
