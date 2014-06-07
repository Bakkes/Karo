#include <CppUnitTest.h>
#include <Windows.h>
#include <string>
#include "RngTimeBased.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {
	char* lltoa(long long val, int base) {

		static char buf[64] = {0};

		int i = 62;
		int sign = (val < 0);
		if(sign) val = -val;

		if(val == 0) return "0";

		for(; val && i ; --i, val /= base) {
			buf[i] = "0123456789abcdef"[val % base];
		}

		if(sign) {
			buf[i--] = '-';
		}
		return &buf[i+1];

	}
	TEST_CLASS(RandomNumberOutputTest) {
		TEST_METHOD(PrintRandomNumbers)
		{
			engine::RngTimeBased rng;
			const int Count = 6400;
			for (int i = 0; i < Count; i++) {
				OutputDebugString(lltoa(rng.NextInteger(), 10));
				OutputDebugString("\r\n");
			}
		}
	};
}