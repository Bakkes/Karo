
#include "CppUnitTest.h"
#include "ComputerPlayer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(MoveInvertionTest) {
	public:
		TEST_METHOD(InvertPlayerMax) {
			Assert::IsTrue(InvertPlayer(Max) == Min);
		}

		TEST_METHOD(InvertPlayerMin) {
			Assert::IsTrue(InvertPlayer(Min) == Max);
		}
	};
}