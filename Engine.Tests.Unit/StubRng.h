#include "IRng.h"

namespace engine {

	class StubRng : public IRng {

	public:
		StubRng::StubRng(int values[]);
		virtual StubRng::~StubRng() override;

		int NextInteger() override;

	private:
		int _pointer;
		int* _values;

	};
}