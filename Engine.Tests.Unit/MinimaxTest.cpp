#include <vector>
#include "CppUnitTest.h"
#include "ComputerPlayer.h"
#include "StubBoard.h"
#include "StubStaticEval.h"
#include "MoveUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(Minimax) {
	public:
		TEST_METHOD(MiniMax_BothCutOff_ReturnsTrue) {
			IBoard* board = new StubBoard();
			ComputerPlayer* ai = new ComputerPlayer(board, 4);
			int results[81] = {
				64, 32, 74, 29, 40,  9,  7, 14, 21, 11, 70,  8, 16,
				57, 28, 36, 89, 12, 45, 50, 19, 15,  2, 65, 46, 78,
				39, 33, 62, 38, 73, 99, 90, 53, 49, 68, 61, 76, 81,
				24,  1, 95, 59,  5, 44, 34, 54, 60, 77, 56, 92, 51,
				80, 43, 13, 10, 86, 26, 94, 100,18, 79, 85, 48, 96,
				30, 27, 71, 87, 17, 37,  4, 20,  6, 25, 82,  3, 47,
				93, 31, 98
			};
			StubStaticEval* staticEval = new StubStaticEval(results, 81);

			ai->SetEvaluator(staticEval);
			Move move = ai->GetBestMove(Max);
			Assert::IsFalse(move.GetToCell() == Vector2D(-1)); // Invalid move structure
			Assert::IsTrue(IsLegalMove(board, move, Max)); // Not legal move
			Assert::AreEqual(37, staticEval->GetCallCount());

			delete board;
			delete ai;
		}

private:
	bool IsLegalMove(IBoard* board, Move move, Players player) {
		std::vector<Move>* legalMoves = board->GetLegalMoves(player);
		for (auto it = legalMoves->begin(); it != legalMoves->end(); ++it) {
			if (MovesAreEqual(move, *it)) {
				return true;
			}
		}
		return false;
	}
	};
}