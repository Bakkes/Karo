
#include "CppUnitTest.h"
#include "ICommunication.h"
#include "Board.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;
using namespace std;
namespace Tests {
	TEST_CLASS(BoardTests) {
	public:
		TEST_CLASS_INITIALIZE(Initialize) {
			// Initialize class.
		}

		TEST_CLASS_CLEANUP(Cleanup) {
			// Cleanup.
		}

		TEST_METHOD(TestConstruction) {
			/** the board should be constructed as a empty 5*4*/
			Board* board = new Board();
			string result = board->ToString();
			int i = 4;
			Assert::IsTrue(
			   "3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
				" ==
				result
			);
		}

		// ReturnNumber returns 5, so this unit test will fail.
		TEST_METHOD(ReturnNumber_Void_Returns4) {
			int expected = 4;
			int actual = engine::ICommunication::Expose();
			Assert::AreNotEqual(expected, actual);
		}
	};
}