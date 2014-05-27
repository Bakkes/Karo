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
		TEST_METHOD_INITIALIZE(InitZobristTest) {
			IRng* _rand = CreateStubRNG();
			for(int cellValue = 0; cellValue < 16; cellValue++) {
				for(int position = 0; position < 400; position++) {
					_hashValues[cellValue][position] = _rand->NextInteger() % 50000;
				}
			}
			delete _rand;
		}

		TEST_METHOD(InitialHash) {
			Board* board = CreateStartingBoard();
			ZobristHashing hasher(board, CreateStubRNG());

			Assert::AreEqual(STARTING_HASH, hasher.GetHash(), L"Invalid Hash");

			delete board;
		}

		int GetCellPosition(const Vector2D& position) {
			return (int)position.Y() * 20 + (int)position.X();
		}

		IRng* CreateStubRNG() {
			int* values = new int[6400];
			for (int i = 0; i < 6400; i++) {
				values[i] = i;
			}
			return new StubRng(values);
		}

		Board* CreateStartingBoard() {
			return Board::CreateBoard(
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
		}

		int _hashValues[16][400];

		static const int STARTING_HASH = 80;
	};
}
