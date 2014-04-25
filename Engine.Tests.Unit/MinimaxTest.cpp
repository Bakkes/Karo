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
		TEST_METHOD(MiniMax_ReturnsTrue) {
			IBoard* board = new StubBoard();
			ComputerPlayer* ai = new ComputerPlayer(board, 8);

			ai->SetEvaluator(new StubStaticEval());
			Move move = ai->GetBestMove(Max);
			Assert::IsFalse(move.GetToCell() == Vector2D(-1)); // Invalid move structure
			Assert::IsTrue(IsLegalMove(board, move, Max)); // Not legal move

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