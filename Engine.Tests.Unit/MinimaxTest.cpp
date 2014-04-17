#include "Board.h"
#include "CppUnitTest.h"
#include "ComputerPlayer.h"
#include "RandStaticEval.h"

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

			delete board;
			delete ai;
		}
	};
}