#include <vector>
#include "CppUnitTest.h"
#include "Board.h"
#include "ZobristHashing.h"
#include "StubRng.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(ZobristHashingTest) {	
	public:
		TEST_METHOD(InitialHash) {
			Board* board = Board::CreateBoard(
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n");
			ZobristHashing hasher(board, CreateStubRNG());

			Assert::AreEqual(-858993428, hasher.GetHash(), L"Invalid Hash");
		}

	private:
		IRng* CreateStubRNG() {
			int* values = new int[6400];
			for (int i = 0; i < 6400; i++) {
				values[i] = i;
			}
			return new StubRng(values);
		}
	};
}
