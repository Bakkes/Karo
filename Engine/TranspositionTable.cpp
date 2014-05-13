#include "TranspositionTable.h"

namespace engine {
	TranspositionTable::TranspositionTable(void)
	{
		map<int,TranspositionTableData> hashMap;
		priority_queue<int> pq;
	}


	TranspositionTable::~TranspositionTable(void)
	{
	}


	void TranspositionTable::Insert(int value, int score, Move* maxBestMove, Move* minBestMove)
	{
		const int size = 1009;

		pq.push(value);
		hashMap[value] = TranspositionTableData(score, maxBestMove, minBestMove);

		if (pq.size > size) {
			hashMap.erase(pq.top());
			pq.pop();
		}
	}

	TranspositionTableData TranspositionTable::Get(int value)
	{
		return hashMap.at(value);
	}
}
