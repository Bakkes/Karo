#pragma once
#include <map>
#include <queue>
#include <iostream>
#include "TranspositionTableData.h"
#include "Move.h"
using namespace std;

namespace engine {
	class ENGINE_API TranspositionTable
	{
	private:
		map<int,TranspositionTableData*>* hashMap;
		priority_queue<int>* pq;
	public:
		TranspositionTable(void);
		~TranspositionTable(void);
		void Insert(int value, int score, Move* maxBestMove, Move* minBestMove);
		TranspositionTableData* Get(int value);
	};
}
