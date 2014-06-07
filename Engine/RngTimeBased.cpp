#include <cstdlib>
#include <time.h>
#include "RngTimeBased.h"

namespace engine {

	RngTimeBased::RngTimeBased() {
		srand(2);
		_returnedNumbers = new std::list<long long>();
	}


	RngTimeBased::~RngTimeBased() {
		delete this->_returnedNumbers;
	}

	long long RngTimeBased::NextInteger() {
		long long rndNumber = CreateLong();
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

	long long RngTimeBased::CreateLong() {
		long long a = rand();
		long long b = rand();

		return (a << 32) | b;
	}

}
