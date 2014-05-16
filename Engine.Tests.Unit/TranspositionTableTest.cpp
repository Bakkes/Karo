#include "CppUnitTest.h"
#include "TranspositionTable.h"
#include "Windows.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(TranspositionTableTest) {
	public:
		TEST_METHOD(TranspositionTableTester) {
			TranspositionTable* tTable = new TranspositionTable();
			
			tTable->Insert(123, 1337, new Move(INSERT, Vector2D(2)), new Move(INSERT, Vector2D(1))); 

			bool check = false;
			if (tTable->Get(123)->GetScore() == 1337) { check = true; }

			delete tTable;

			Assert::IsTrue(check);
		}
	};
}