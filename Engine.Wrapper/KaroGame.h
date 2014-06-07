#pragma once

#include "MoveWrapper.h"
#include "Board.h"
#include "PlayersWrapper.h"
#include "BoardWrapper.h"
#include "TranspositionTable.h"
#include "ZobristHashing.h"

using namespace engine;

namespace engine {
namespace wrapper {
	public ref class KaroGame
	{
		public:
			KaroGame();
			~KaroGame();
			!KaroGame();
			MoveWrapper^ GetBestMove();
			void ExecuteMove(MoveWrapper^ w, engine::wrapper::Players player);
			void UndoMove(MoveWrapper^ w, engine::wrapper::Players player);
			bool HasWon(engine::wrapper::Players player);
			BoardWrapper^ GetBoard();
			int GetStaticEvalCallCount();
			int GetNodesSeenCount();
		private:
			BoardWrapper^ _board;
			TranspositionTable* _transpositionTable;
			ZobristHashing* _hasher;

			int _staticEvalCallCount;
			int _nodesSeen;
	};
}
}