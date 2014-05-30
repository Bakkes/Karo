#include "TranspositionTable.h"

namespace engine {
	TranspositionTable::TranspositionTable(int maxSize)
	{
		_hashMap = new map<int,TranspositionTableData*>();
		_ageQueue = new queue<int>();
	}


	TranspositionTable::~TranspositionTable(void)
	{
		delete _hashMap;
		delete _ageQueue;
	}


	void TranspositionTable::Insert(int value, int score, Move* maxBestMove, Move* minBestMove)
	{
		_ageQueue->push(value);
		(*_hashMap)[value] = new TranspositionTableData(score, maxBestMove, minBestMove); //this breaks EVERYTHING!!!

		if (_ageQueue->size() > _maxSize) {
			_hashMap->erase(_ageQueue->front());
			_ageQueue->pop();
		}
	}

	bool TranspositionTable::Contains(int key) {
		return _hashMap->find(key) != _hashMap->end();
	}

	TranspositionTableData* TranspositionTable::Get(int value)
	{
		return _hashMap->at(value);
	}
}
