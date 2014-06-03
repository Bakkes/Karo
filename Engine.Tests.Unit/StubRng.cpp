#include "StubRng.h"

namespace engine {

	StubRng::StubRng(int values[]) {
		_pointer = 0;
		_values = values;
	}

	StubRng::~StubRng() {
		delete _values;
	}

	int StubRng::NextInteger() {
		return _values[_pointer++];
	}
}