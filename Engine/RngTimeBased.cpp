#include <cstdlib>
#include <time.h>
#include "RngTimeBased.h"

namespace engine {

	RngTimeBased::RngTimeBased() {
		srand((unsigned)time(NULL));
	}


	RngTimeBased::~RngTimeBased() {
	}

	int RngTimeBased::NextInteger() {
		return rand();
	}

}