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

	void TranspositionExtension::RegisterBoard(EvalResult& result, int depth, Players player) {
		long long hash = _hasher->GetHash();
		Move* move = new Move(result.GetMove());

		_transpositionTable->Insert(hash, depth, result.GetScore(), player, move);
	}

	void TranspositionExtension::UpdateMoves(std::vector<Move>& moves, Players player, int depth) {
		long long hash = _hasher->GetHash();

		if (!_transpositionTable->Contains(hash)) {
			// We don't know this board
			return;
		}

		TranspositionTableData* data = _transpositionTable->Get(hash);

		if (data->GetBestMove(player) == nullptr) {
			// We don't know a move for this player
			return;
		}

		if (data->GetDepth() <= depth) {
			// We've seen this board before at the same depth or earlier
			// If it's earlier than that search went deeper and has a better result
			// We can already say what the result is

			bool containsMove = find(moves.begin(), moves.end(), *data->GetBestMove(player)) != moves.end();

			if (containsMove) {

				std::cout << "zobrist, Nodes saved: " << (moves.size() - 1) << std::endl;

				moves.clear();
				moves.push_back(Move(*data->GetBestMove(player)));
			} else {
				std::cout << "zobrist COLLISION DETECTED!" << std::endl;
			}
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
