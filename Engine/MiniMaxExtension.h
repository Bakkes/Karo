#pragma once
#include "AIExtension.h"
namespace engine{
	class MiniMaxExtension : public AIExtension
	{
	public:
		MiniMaxExtension(void);
		~MiniMaxExtension(void);
		void Step(const Players& player, const int& currentDepth, EvalResult&) override;
		bool ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player) override;
	};

}