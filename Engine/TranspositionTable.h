#pragma once
#include <map>
#include <queue>
#include <iostream>
#include "TranspositionTableData.h"
#include "Move.h"
#include "Players.h"
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
		void Insert(int value, int score, Move* bestMove, int depth);
		bool Contains(int key);
		TranspositionTableData* Get(int value);
	};
}
