#include <cstdlib>
#include <time.h>
#include <random>
#include <cmath>
#include "RngTimeBased.h"

namespace engine {

	RngTimeBased::RngTimeBased() {
		srand(2);
		_returnedNumbers = new std::list<long long>();
		_mersenne = new std::mt19937_64(0);
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

	long long RngTimeBased::CreateLong() {
		long long rnd = 0;
		for (int i = 0; i < 8; i++) {
			long long val = rand() & 0xFF;

			rnd |= (val << (i * 8));
		}

		return rnd;
	}

}
