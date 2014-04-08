#include "CppUnitTest.h"
#include "MyMath.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
	TEST_CLASS(MyMathTests)
	{
	public:
		TEST_CLASS_INITIALIZE(Setup) {
			_math = new Karo::MyMath();
		}

		TEST_CLASS_CLEANUP(Cleanup) {
			delete _math;
		}

		TEST_METHOD(Add_TwoNumbers_ReturnSumOfTwoNumbers) {
			double a = 5;
			double b = 10;
			double expected = 15;
			double actual = _math->Add(a, b);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(Power_NegativePower_SmallerNumber) {
			double a = 2;
			double b = -1;
			double actual = _math->Add(a, b);
			// Check if it is in range.
			Assert::IsTrue(actual < 0.51 && actual > 0.49);
		}
	private:
		static Karo::MyMath* _math;
	};
}