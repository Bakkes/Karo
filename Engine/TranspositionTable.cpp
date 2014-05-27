#include "TranspositionTable.h"

namespace engine {
	TranspositionTable::TranspositionTable(void)
	{
		hashMap = new map<int,TranspositionTableData*>();
		pq = new priority_queue<int>();
	}


	TranspositionTable::~TranspositionTable(void)
	{
		delete hashMap;
		delete pq;
	}


	void TranspositionTable::Insert(int value, int score, Move* maxBestMove, Move* minBestMove)
	{
		const int size = 1009;

		pq->push(value);
		(*hashMap)[value] = new TranspositionTableData(score, maxBestMove, minBestMove); //this breaks EVERYTHING!!!

		if (pq->size() > size) {
			hashMap->erase(pq->top());
			pq->pop();
		}
	}

	bool TranspositionTable::Contains(int key) {
		return hashMap->find(key) != hashMap->end();
	}

	TranspositionTableData* TranspositionTable::Get(int value)
	{
		return hashMap->at(value);
	}
}
