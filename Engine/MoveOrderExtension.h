#include "AIExtension.h"
#pragma once
namespace engine{
	class MoveOrderExtension : public AIExtension
	{
	public:
		MoveOrderExtension();
		~MoveOrderExtension(void);
		void Step(const Players& player,const int& currentDepth, EvalResult&);
		void UpdateMoves(const int& depth,std::vector<Move>& moves);
	private:
		bool _shouldOrder;
		Players _player;
	};
}