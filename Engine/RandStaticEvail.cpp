#include "RandStaticEvail.h"

namespace engine {
	RandStaticEvail::RandStaticEvail() {
	}

	RandStaticEvail::~RandStaticEvail()	{
	}

	int RandStaticEvail::Eval(IBoard* board, Players player) {
		return rand();
	}
}
