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

		// proofs that asigning somthing from a defrenced value wil be a copy
		TEST_METHOD(StackVsHeapLogic) {
			int* d = new int(3);
			int* b = new int(5);
			{
				int c = *d;
				*b = c;
				c += 5;
			}
			Assert::AreEqual(3, *b);
		};
		TEST_METHOD(CopyOnDerefernce) {
			int* d = new int(3);
			int* b = new int(5);

			*b = *d;
			*d += 5;

			Assert::AreEqual(3, *b);
			Assert::AreEqual(8, *d);
		};
		TEST_METHOD(CopyOnDeclare) {
			int* d = new int(3);
			int* b = new int(*d);
			*d += 5;
			Assert::AreEqual(3, *b);
			Assert::AreEqual(8, *d);
		};
	};
}
