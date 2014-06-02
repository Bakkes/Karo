#include <assert.h>
#include "TranspositionExtension.h"
#include "RngTimeBased.h"

namespace engine {

	TranspositionExtension::TranspositionExtension() {
		_transpositionTable = new TranspositionTable(1000);
		_ownerOfTable = true;
	}

	TranspositionExtension::TranspositionExtension(TranspositionTable* transpostionTable) {
		_transpositionTable = transpostionTable;
		_ownerOfTable = false;
	}

	TranspositionExtension::~TranspositionExtension() {
		if (_ownerOfTable) {
			delete _transpositionTable;
		}
		delete _hasher;
	}

	void TranspositionExtension::Start(const int& maxDepth, IBoard* board, IStaticEvaluation* evaluation) {
		AIExtension::Start(maxDepth, board, evaluation);
		IRng* rand = new RngTimeBased();
		_hasher = new ZobristHashing(board, rand);
		delete rand;
	}

	void TranspositionExtension::RegisterBoard(EvalResult& result) {
		int hash = _hasher->GetHash();
		Move* move = new Move(result.GetMove());

		_transpositionTable->Insert(hash, result.GetScore(), move);
	}

	void TranspositionExtension::UpdateMoves(std::vector<Move>& moves) {
		int hash = _hasher->GetHash();

		if (!_transpositionTable->Contains(hash)) {
			return;
		}

		TranspositionTableData* data = _transpositionTable->Get(hash);

		int findResult = find(moves.begin(), moves.end(), *data->GetBestMove()) - moves.begin();
		
		assert(findResult >= 0);

		if (findResult > 0 && ((unsigned)findResult < moves.size())) {
			Move tmp = moves[findResult];
			moves[findResult] = moves[0];
			moves[0] = tmp;
		}
	}

}
