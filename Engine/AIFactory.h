#pragma once
#include "AI.h"
#include "AlfaBetaExtension.h"
#include "MoveSwapExtension.h"
namespace engine{
	class ENGINE_API AIFactory
	{
	public:
		AIFactory(IBoard* board, int maxDepth);
		~AIFactory(void);

		// just a simple minmax ai
		AI* CreateAI();
		// an AI that does alfa beta pruning
		AI* CreateAlfaAI();
		// an AI that does alfa beta prunging with move oredring
		AI* CreateMoveOrderingAlfaAI();

		IBoard* GetBoard() const;
	private:
		IBoard* _board;
		int _maxDepth;
	};
}