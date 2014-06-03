#include <cstdlib>
#include <time.h>
#include "RngTimeBased.h"

namespace engine {

	RngTimeBased::RngTimeBased() {
		srand((unsigned)time(NULL));
		_returnedNumbers = new std::list<int>();
	}


	RngTimeBased::~RngTimeBased() {
		delete this->_returnedNumbers;
	}

	int RngTimeBased::NextInteger() {
		int rndNumber = rand();
		for (auto it = _returnedNumbers->begin(); it != _returnedNumbers->end(); ++it) {
			if (*it == rndNumber) {
				// This is a duplicate! This is not allowed!
				return this->NextInteger();
			}
		}
		// Not a duplicate, add it and return it
		_returnedNumbers->push_front(rndNumber);
		return rndNumber;
	}

	long long RngTimeBased::NextLongLong() {
		return static_cast<long long>((rand() << 32) | rand());
	}
}