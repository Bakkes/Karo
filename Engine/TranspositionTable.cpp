#include "TranspositionTable.h"

namespace engine {
	TranspositionTable::TranspositionTable(int maxSize)
	{
		_hashMap = new map<int,TranspositionTableData*>();
		_ageQueue = new queue<int>();
		_maxSize = maxSize;
	}


	TranspositionTable::~TranspositionTable(void)
	{
		delete _hashMap;
		delete _ageQueue;
	}


	void TranspositionTable::Insert(int key, int score, Move* bestMove)
	{
		if (_ageQueue->size() >= (unsigned) _maxSize) {
			// Remove an item if we reached the limit
			_hashMap->erase(_ageQueue->front());
			_ageQueue->pop();
		}

		_ageQueue->push(key);
		(*_hashMap)[key] = new TranspositionTableData(score, bestMove);
	}

	bool TranspositionTable::Contains(int key) {
		return _hashMap->find(key) != _hashMap->end();
	}

	TranspositionTableData* TranspositionTable::Get(int value)
	{
		return _hashMap->at(value);
	}
}
