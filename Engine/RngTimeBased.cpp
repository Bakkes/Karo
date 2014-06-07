#include <cstdlib>
#include <time.h>
#include <random>
#include <cmath>
#include "RngTimeBased.h"

namespace engine {

	RngTimeBased::RngTimeBased() {
		srand(2);
		_returnedNumbers = new std::list<long long>();
		_randDevice = new std::random_device();
		_mersenne = new std::mt19937_64((*_randDevice)());
		_dist = new std::uniform_int_distribution<long long int>(-(long long)(9223372036854775808), 9223372036854775807);
	}


	RngTimeBased::~RngTimeBased() {
		delete this->_returnedNumbers;
		delete this->_mersenne;
		delete this->_randDevice;
		delete this->_dist;
	}

	long long RngTimeBased::NextInteger() {
		long long rndNumber = (*_dist)(_mersenne);
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
