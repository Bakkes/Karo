#include <cstdlib>
#include <time.h>
#include <random>
#include <cmath>
#include "RngTimeBased.h"

namespace engine {

	RngTimeBased::RngTimeBased() {
		_returnedNumbers = new std::list<long long>();
		_mersenne = new std::mt19937_64(1);
	}


	RngTimeBased::~RngTimeBased() {
		delete this->_returnedNumbers;
		delete this->_mersenne;
	}

	long long RngTimeBased::NextInteger() {
		long long rndNumber = (*_mersenne)();
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

}
