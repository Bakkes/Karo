#include "AIExtension.h"
#pragma once
namespace engine{
	class MoveOrderExtension : AIExtension
	{
	public:
		MoveOrderExtension(void);
		~MoveOrderExtension(void);
		void Step(const Players& player,const int& currentDepth, EvalResult&);
		void UpdateMoves(const int& depth,std::vector<Move>& moves);
	};
}