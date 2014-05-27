
#include "ZobristHashing.h"

namespace engine{

	ZobristHashing::ZobristHashing() {
		srand((unsigned)time(NULL));
	
		for(int i = 0; i < 16; i++) {
			for(int j = 0; j < 400; j++) {
				_hashValues[i][j] = rand() % 1000;
			}
		}
	}

	ZobristHashing::~ZobristHashing() {
	}

	void ZobristHashing::ExecuteMove(const Move&) {
	}

	void ZobristHashing::UndoMove(const Move&) {
	}

	int ZobristHashing::GetHash() const {
		return 0;
	}

}
