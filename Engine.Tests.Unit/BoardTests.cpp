
#include "CppUnitTest.h"
#include "ICommunication.h"
#include "Board.h"
#include <string>
#include <iostream>
#include "Windows.h"

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
			OutputDebugString(result.c_str());
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
	};
}