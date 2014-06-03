#include "IRng.h"

namespace engine {

	class StubRng : public IRng {

	public:
		StubRng::StubRng(int values[]);
		virtual StubRng::~StubRng() override;

		int NextInteger() override;
		long long NextLongLong() override { return 0l;}

	private:
		int _pointer;
		int* _values;

	};
}