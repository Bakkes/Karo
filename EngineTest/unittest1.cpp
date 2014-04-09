#include "CppUnitTest.h"
#include "MathFuncsLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Karo;

namespace EngineTest
{		
	TEST_CLASS(MyMathTests)
	{
	public:
		TEST_CLASS_INITIALIZE(Setup) {
			
		}

		TEST_CLASS_CLEANUP(Cleanup) {
			
		}

		TEST_METHOD(Add_TwoNumbers_ReturnSumOfTwoNumbers) {
			double a = 5;
			double b = 10;
			double expected = 15;
			double actual = MyMathFuncs::Add(a, b);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Power_NegativePower_SmallerNumber) {
			double a = 2;
			double b = -1;
			double actual = MyMathFuncs::Add(a, b);
			// Check if it is in range.
			Assert::IsTrue(actual < 0.51 && actual > 0.49);
		};
	};
}