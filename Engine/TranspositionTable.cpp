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


	void TranspositionTable::Insert(int key, int score, Move* bestMove, Players player)
	{
		TranspositionTableData* data = nullptr;

		if (Contains(key)) {
			// Fetch existing item
			data = _hashMap->at(key);
		} else {
			// Insert new item

			if (_ageQueue->size() >= (unsigned) _maxSize) {
				// Remove an item if we reached the limit
				_hashMap->erase(_ageQueue->front());
				_ageQueue->pop();
			}

			data = new TranspositionTableData(score);

			_ageQueue->push(key);
			(*_hashMap)[key] = data;
		}

		// Set the best move
		if (player == Max) {
			data->SetMaxBestMove(bestMove);
		} else {
			data->SetMinBestMove(bestMove);
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
