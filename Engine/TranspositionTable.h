#pragma once
#include <unordered_map>
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
		unordered_map<long long, TranspositionTableData*>* _hashMap;
		queue<long long>* _ageQueue;
		int _maxSize;
	public:
		TranspositionTable(int maxSize);
		~TranspositionTable(void);
		void Insert(long long key, int depth, int score, Players player, Move* bestMove);
		bool Contains(long long key);
		TranspositionTableData* Get(long long key);
	};
}
