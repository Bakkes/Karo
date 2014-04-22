#include <vector>
#include "Board.h"
#include "CppUnitTest.h"
#include "ComputerPlayer.h"
#include "RandStaticEval.h"
#include "MoveUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(Minimax) {
	public:
		TEST_METHOD(MiniMaxDepth_0) {
			IBoard* board = new Board();
			ComputerPlayer* ai = new ComputerPlayer(board, 0);

			ai->SetEvaluator(new RandStaticEval());
			Move move = ai->GetBestMove(Max);
			Assert::IsFalse(move.GetToTile() == Vector2D(-1));
			Assert::IsTrue(IsLegalMove(board, move, Max));

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