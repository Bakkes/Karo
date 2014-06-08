#include <vector>
#include "CppUnitTest.h"
#include "BigInteger.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(BigInterTest) {
	public:

		TEST_METHOD(BI_XOR) {
			BigInteger a(1);
			BigInteger b(1);
			BigInteger c = a ^ b;
			
			a ^= b;

			BigInteger expected(0);

			Assert::IsTrue(expected == c, L"a ^ b failed");
			Assert::IsTrue(expected == a, L"a ^= b failed");
		}

		TEST_METHOD(BI_LargerThan) {
			BigInteger a(2);
			BigInteger b(1);

			Assert::IsTrue(a > b);
			Assert::IsFalse(b > a);
		}

		TEST_METHOD(BI_SmallerThan) {
			BigInteger a(1);
			BigInteger b(2);

			Assert::IsTrue(a < b);
			Assert::IsFalse(b < a);
		}

		TEST_METHOD(BI_LargerOrEqualsThan) {
			BigInteger a(2);
			BigInteger b(2);
			BigInteger c(3);

			Assert::IsTrue(a >= b);
			Assert::IsTrue(c >= b);
		}

		TEST_METHOD(BI_SmallerOrEqualsThan) {
			BigInteger a(2);
			BigInteger b(2);
			BigInteger c(1);

			Assert::IsTrue(a <= b);
			Assert::IsTrue(c <= b);
		}
	};
}
