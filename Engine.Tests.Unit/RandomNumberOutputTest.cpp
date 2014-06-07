#include <CppUnitTest.h>
#include <Windows.h>
#include <string>
#include "RngTimeBased.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {
	TEST_CLASS(RandomNumberOutputTest) {
		TEST_METHOD(PrintRandomNumbers)
		{
			engine::RngTimeBased rng;
			const int Count = 6400;
			for (int i = 0; i < Count; i++) {
				char *buffer = new char[20];
				_ltoa_s(rng.NextInteger(), buffer, 20, 10);
				OutputDebugString(buffer);
				OutputDebugString("\r\n");
				delete[] buffer;
			}
		}
	};
}