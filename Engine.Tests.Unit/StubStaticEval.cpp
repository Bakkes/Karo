#include "StubStaticEval.h"

namespace engine {
	StubStaticEval::StubStaticEval(int results[], int size) {
		_results = results;
		_resultCount = size;
		_pointer = -1;
		_callCount = 0;
	}

	StubStaticEval::~StubStaticEval() {
	}

	int StubStaticEval::Eval(IBoard* board, Players player) {
		++_callCount;
		return _results[(++_pointer) % _resultCount];
	}

	const int& StubStaticEval::GetCallCount() const {
		return _callCount;
	}
}
