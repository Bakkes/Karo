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

	void TranspositionExtension::RegisterBoard(const Players& player, EvalResult& result) {
		int hash = _hasher->GetHash();
		Move* move = new Move(result.GetMove());

		_transpositionTable->Insert(hash, result.GetScore(), move);
	}

	bool TranspositionExtension::IsKnownBoard(const Players& player, EvalResult& result) {
		int hash = _hasher->GetHash();

		if (!_transpositionTable->Contains(hash)) {
			return false;
		}

		TranspositionTableData* data = _transpositionTable->Get(hash);

		result.SetScore(data->GetScore());
		// Create copies of the stored move to prevent possible deletion later on
		result.SetMove(Move(*data->GetBestMove()));

		return true;
	}
}
