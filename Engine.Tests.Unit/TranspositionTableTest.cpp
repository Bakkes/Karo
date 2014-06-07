#include "CppUnitTest.h"
#include "TranspositionTable.h"
#include "Windows.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(TranspositionTableTest) {
	public:
		TEST_METHOD(TranspositionTableTester) {
			TranspositionTable* tTable = new TranspositionTable(1000);
			
			Move* move = new Move(INSERT, Vector2D(2));

			tTable->Insert(123, 0, 1337, Max, move); 

			Assert::AreEqual(1337, tTable->Get(123)->GetScore(), L"Score mismatch");
			Assert::IsTrue(move == tTable->Get(123)->GetBestMove(Max), L"Mismatch in best move for max");

			delete tTable;
			delete move;
		}
	};
}