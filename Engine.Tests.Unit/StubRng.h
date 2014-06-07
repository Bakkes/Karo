#include "IRng.h"

namespace engine {

	class StubRng : public IRng {

	public:
		StubRng::StubRng(long long values[]);
		virtual StubRng::~StubRng() override;

		long long NextInteger() override;

	private:
		int _pointer;
		long long* _values;

	};
}