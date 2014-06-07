#pragma once
#include <map>
#include <queue>
#include <gmp.h>
#include "TranspositionTableData.h"
#include "Move.h"
#include "Players.h"
#include "BigInteger.h"
using namespace std;

namespace engine {
	class ENGINE_API TranspositionTable
	{
	private:
		map<BigInteger, TranspositionTableData*>* _hashMap;
		queue<BigInteger>* _ageQueue;
		int _maxSize;
	public:
		TranspositionTable(int maxSize);
		~TranspositionTable(void);
		void Insert(BigInteger key, int depth, int score, Players player, Move* bestMove);
		bool Contains(BigInteger key);
		TranspositionTableData* Get(BigInteger key);
	};
}
