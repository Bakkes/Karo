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
		map<int,TranspositionTableData*>* _hashMap;
		queue<int>* _ageQueue;
		int _maxSize;
	public:
		TranspositionTable(int maxSize);
		~TranspositionTable(void);
		void Insert(int value, int score, Move* maxBestMove, Move* minBestMove);
		bool Contains(int key);
		TranspositionTableData* Get(int value);
	};
}
