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
		bool ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player) override;

	private:
		IHashAlgorithm* _hasher;
		TranspositionTable* _transpositionTable;
	};
}
