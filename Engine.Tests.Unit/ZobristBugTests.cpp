#include <CppUnitTest.h>
#include <map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {
	TEST_CLASS(ZobristBugTests) {
		// Tests for collisions by calculating the hash of a lot of boards.
		// If we calculate the same hash for two different board states,
		// the test will fail.
		TEST_METHOD(TestForCollisions) {
		}
	};
}