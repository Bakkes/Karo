#pragma once

#include <iostream>
#include <time.h>
#include <hash_map>
#include "Board.h"
#include "IHashAlgorithm.h"

#define m 16
#define n 400

namespace engine{
	class ZobristHashing : IHashAlgorithm{

	private:
		hash_map<int,int> tableHash;
		int table[m][n];

	public:
		ZobristHashing(void);
		~ZobristHashing(void);

		void init_zobrist();
		void board_hash();
		int hash(Board a) override;













	};
}