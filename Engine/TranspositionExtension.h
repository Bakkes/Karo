#pragma once
#include "AIExtension.h"
#include "TranspositionTable.h"
#include "ZobristHashing.h"

namespace engine {
	class TranspositionExtension : public AIExtension
	{
	public:
		TranspositionExtension();
		TranspositionExtension(TranspositionTable* table);
		virtual ~TranspositionExtension();

		void Start(const int& maxDepth, IBoard* board, IStaticEvaluation* evaluation) override;
		void RegisterBoard(EvalResult& result) override;
		void UpdateMoves(std::vector<Move>& moves) override;

	private:
		IHashAlgorithm* _hasher;
		TranspositionTable* _transpositionTable;
		// Knows if we should delete the hash table upon destruction
		bool _ownerOfTable;
	};
}
