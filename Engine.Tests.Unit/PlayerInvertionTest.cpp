
#include "CppUnitTest.h"
#include "ComputerPlayerUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(MoveInvertionTest) {
	public:
		TEST_METHOD(InvertPlayerMax) {
			Assert::IsTrue(ComputerPlayerUtils::InvertPlayer(Max) == Min);
		}

		TEST_METHOD(InvertPlayerMin) {
			Assert::IsTrue(ComputerPlayerUtils::InvertPlayer(Min) == Max);
		}
	};
}