#include <assert.h>
#include "TranspositionExtension.h"
#include "RngTimeBased.h"

namespace engine {

	TranspositionExtension::TranspositionExtension() {
		_transpositionTable = new TranspositionTable(1000);
		_ownerOfTable = true;
		_hasher = nullptr;
	}

	TranspositionExtension::TranspositionExtension(ZobristHashing* hasher, TranspositionTable* transpostionTable) {
		_transpositionTable = transpostionTable;
		_hasher = hasher;
		_ownerOfTable = false;
	}

	TranspositionExtension::~TranspositionExtension() {
		if (_ownerOfTable) {
			delete _transpositionTable;
			delete _hasher;
		}
	}

	void TranspositionExtension::Start(const int& maxDepth, IBoard* board, IStaticEvaluation* evaluation) {
		AIExtension::Start(maxDepth, board, evaluation);
		if (_hasher == nullptr) {
			IRng* rand = new RngTimeBased();
			_hasher = new ZobristHashing(board, rand);
			delete rand;
		}
		_hasher->UpdateBoard(board);
	}

	void TranspositionExtension::RegisterBoard(EvalResult& result, int depth) {
		int hash = _hasher->GetHash();
		Move* move = new Move(result.GetMove());

		_transpositionTable->Insert(hash, result.GetScore(), move, depth);
	}

	void TranspositionExtension::UpdateMoves(std::vector<Move>& moves, int depth) {
		int hash = _hasher->GetHash();

		if (!_transpositionTable->Contains(hash)) {
			return;
		}

		TranspositionTableData* data = _transpositionTable->Get(hash);

		if (data->GetDepth() == depth) {
			// We've seen this board before at the same depth or earlier
			// If it's earlier than that search went deeper and has a better result
			// We can already say what the result is
			moves.clear();
			moves.push_back(Move(*data->GetBestMove()));
		} else if (data->GetDepth() > depth) {
			// We've seen this board before but at a deeper level, this search will improve that
			// We can use our result from previous search to order the moves a bit
			/*int findResult = find(moves.begin(), moves.end(), *data->GetBestMove()) - moves.begin();
		
			assert(findResult >= 0);

			if (findResult > 0 && ((unsigned)findResult < moves.size())) {
				Move tmp = moves[findResult];
				moves[findResult] = moves[0];
				moves[0] = tmp;
			}*/
		}
	}

}
