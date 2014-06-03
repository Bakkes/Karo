#pragma once
#include "AI.h"
#include "AlfaBetaExtension.h"
#include "MoveSwapExtension.h"
#include "MiniMaxExtension.h"
#include "MoveOrderExtension.h"
#include "TranspositionExtension.h"

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

		AI* CreateMoveOrderingAlfaZorbristAI();
		AI* CreateMoveOrderingAlfaZorbristAI(TranspositionTable* table);

		IBoard* GetBoard() const;
	private:
		IBoard* _board;
		int _maxDepth;
	};
}