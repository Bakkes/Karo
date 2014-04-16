#include "CppUnitTest.h"
#include "ICommunication.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {
	TEST_CLASS(ClassNameTests) {
	public:
		TEST_CLASS_INITIALIZE(Initialize) {
			// Initialize class.
		}

		TEST_CLASS_CLEANUP(Cleanup) {
			// Cleanup.
		}

		TEST_METHOD(MethodName_Input_ExpectedResults) {
			// Do stuff
			Assert::IsTrue(true);
		}

		// ReturnNumber returns 5, so this unit test will fail.
		TEST_METHOD(ReturnNumber_Void_Returns4) {
			int expected = 4;
			int actual = engine::ICommunication::Expose();
			Assert::AreNotEqual(expected, actual);
		}
	};
}
