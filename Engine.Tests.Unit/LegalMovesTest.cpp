#include <vector>
#include "CppUnitTest.h"
#include "Board.h"
#include "MoveUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(LegalMoves) {
	public:
		TEST_METHOD(RulesAmendment) {
			Board* board = Board::CreateBoard(
				"1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,1,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,3,5,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n",
				Vector2D(0, 0));

			std::vector<Move>* legalMoves = board->GetLegalMoves(Min);

			Move illegalMove = Move(STEP, Vector2D(0, 0), Vector2D(1, 0), Vector2D(0, 1));

			for (auto it = legalMoves->begin(); it != legalMoves->end(); ++it) {
				Move move = *it;

				Assert::IsFalse(MovesAreEqual(illegalMove, move), L"Found illegal move as specified by rule amendment");
			}

			delete legalMoves;
			delete board;
		}
	};
}