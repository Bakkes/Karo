#include "StubRng.h"

namespace engine {

	StubRng::StubRng(long long values[]) {
		_pointer = 0;
		_values = values;
	}

	StubRng::~StubRng() {
		delete _values;
	}

	long long StubRng::NextInteger() {
		return _values[_pointer++];
	}
}