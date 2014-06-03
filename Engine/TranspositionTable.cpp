#include "TranspositionTable.h"

namespace engine {
	TranspositionTable::TranspositionTable(int maxSize)
	{
		_hashMap = new map<long long,TranspositionTableData*>();
		_ageQueue = new queue<long long>();
		_maxSize = maxSize;
	}


	TranspositionTable::~TranspositionTable(void)
	{
		delete _hashMap;
		delete _ageQueue;
	}


	void TranspositionTable::Insert(long long key, int score, Move* bestMove, int depth)
	{
		if (_ageQueue->size() >= (unsigned) _maxSize) {
			// Remove an item if we reached the limit
			_hashMap->erase(_ageQueue->front());
			_ageQueue->pop();
		}

		_ageQueue->push(key);
		(*_hashMap)[key] = new TranspositionTableData(score, bestMove, depth);
	}

	bool TranspositionTable::Contains(long long key) {
		return _hashMap->find(key) != _hashMap->end();
	}

	TranspositionTableData* TranspositionTable::Get(long long value)
	{
		return _hashMap->at(value);
	}
}
