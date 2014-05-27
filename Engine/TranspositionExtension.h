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

		bool ShouldContinue(const IBoard* board, const EvalResult& currentResult, EvalResult& prevResult, const Players& player);

	private:
		IHashAlgorithm* _hasher;
		TranspositionTable* _transpositionTable;
	};
}
