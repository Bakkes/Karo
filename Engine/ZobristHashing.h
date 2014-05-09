#pragma once
#pragma warning(disable:4251)

#include <iostream>
#include <time.h>
#include <hash_map>
#include "Board.h"
#include "IHashAlgorithm.h"



namespace engine{
	class ENGINE_API ZobristHashing : IHashAlgorithm{

	private:
		hash_map<int,int> tableHash;
		

		int table[16][400];

	public:
		ZobristHashing(void);
		~ZobristHashing(void);

		void init_zobrist();
		void board_hash();
		int hash(Board a) override;













	};
}