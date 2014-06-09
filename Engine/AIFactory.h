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
		AIFactory(IBoard* board, ZobristHashing* hasher, TranspositionTable* table, int maxDepth);
		~AIFactory(void);

		// create an ai, a higher number means a more fancy ai
		AI* CreateAI(unsigned which);

		// just a simple minmax ai
		AI* CreateAI();
		// an AI that does alfa beta pruning
		AI* CreateAlfaAI();
		// an AI that does alfa beta prunging with move oredring
		AI* CreateMoveOrderingAlfaAI();

		AI* CreateMoveOrderingAlfaZorbristAI();

		IBoard* GetBoard() const;
	private:
		IBoard* _board;
		ZobristHashing* _hasher;
		TranspositionTable* _table;
		int _maxDepth;
	};
}