#pragma once
#include "AIExtension.h"
#include "TranspositionTable.h"
#include "ZobristHashing.h"

namespace engine {
	class TranspositionExtension : public AIExtension
	{
	public:
		TranspositionExtension();
		virtual ~TranspositionExtension();

		void Start(const int& maxDepth, IBoard* board, IStaticEvaluation* evaluation) override;
		void RegisterBoard(const Players& player, EvalResult& result) override;
		bool IsKnownBoard(const Players& player, EvalResult& result) override;

	private:
		IHashAlgorithm* _hasher;
		TranspositionTable* _transpositionTable;
	};
}
