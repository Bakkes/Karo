#pragma once
#include "AIExtension.h"
#include "TranspositionTable.h"
#include "ZobristHashing.h"

namespace engine {
	class TranspositionExtension : public AIExtension
	{
	public:
		TranspositionExtension();
		TranspositionExtension(ZobristHashing* hasher, TranspositionTable* table);
		virtual ~TranspositionExtension();

		void Start(const int& maxDepth, IBoard* board, IStaticEvaluation* evaluation) override;
		void RegisterBoard(EvalResult& result, int depth, Players player) override;
		void UpdateMoves(std::vector<Move>& moves, Players player, int depth) override;

	private:
		IHashAlgorithm* _hasher;
		TranspositionTable* _transpositionTable;
		// Knows if we should delete the hash table upon destruction
		bool _ownerOfTable;
	};
}
