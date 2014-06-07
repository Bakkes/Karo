#include "TranspositionTable.h"

namespace engine {
	TranspositionTable::TranspositionTable(int maxSize)
	{
		_hashMap = new map<BigInteger,TranspositionTableData*>();
		_ageQueue = new queue<BigInteger>();
		_maxSize = maxSize;
	}


	TranspositionTable::~TranspositionTable(void)
	{
		delete _hashMap;
		delete _ageQueue;
	}


	void TranspositionTable::Insert(BigInteger key, int depth, int score, Players player, Move* bestMove)
	{
		TranspositionTableData* data = nullptr;

		if (Contains(key)) {
			// Update to an item
			data = _hashMap->at(key);
		} else if (_ageQueue->size() >= (unsigned) _maxSize) {
			// Remove an item if we reached the limit
			_hashMap->erase(_ageQueue->front());
			_ageQueue->pop();
		}

		if (data == nullptr) {
			// New item
			data = new TranspositionTableData(score, depth);
			_ageQueue->push(key);
		}

		data->SetBestMove(player, bestMove);
		(*_hashMap)[key] = data;
	}

	bool TranspositionTable::Contains(BigInteger key) {
		return _hashMap->find(key) != _hashMap->end();
	}

	TranspositionTableData* TranspositionTable::Get(BigInteger value) {
		return _hashMap->at(value);
	}
}
