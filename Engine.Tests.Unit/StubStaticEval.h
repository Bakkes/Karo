#pragma once

#include "IStaticEvaluation.h"

namespace engine {

	class StubStaticEval : public IStaticEvaluation {
	public:
		StubStaticEval(int results[], int size);
		~StubStaticEval();

		int Eval(IBoard* board, Players player) override;
		const int& GetCallCount() const;

	private:
		int _pointer;
		int* _results;
		int _resultCount;
		int _callCount;
	};
}
