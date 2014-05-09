#include "CppUnitTest.h"
#include "Board.h"
#include "Cell.h"
#include <string>
#include <iostream>
#include "Windows.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;
using namespace std;
namespace Tests {
	TEST_CLASS(MoveFinder) {
	private:
		Board* board;
		Move* move;
	public:
		TEST_METHOD_INITIALIZE(CreateBoard) {
			board = Board::CreateBoard(
				"5,3,3,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,5,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,1,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"5,3,1,5,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
			);
			move = NULL;
		}

		TEST_METHOD_CLEANUP(DeleteBoard) {
			delete board;
			delete move;
		}

		TEST_METHOD(MTinsertTest) {
			board = Board::CreateBoard(
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
			);
			vector<Move>* resultMax = board->GetLegalMoves(Max);
			vector<Move>* resultMin = board->GetLegalMoves(Min);
			Assert::IsTrue(*resultMax == *resultMin);

			Move moves[] = {
				Move(INSERT, Vector2D(0,0)),
				Move(INSERT, Vector2D(1,0)),
				Move(INSERT, Vector2D(2,0)),
				Move(INSERT, Vector2D(3,0)),
				Move(INSERT, Vector2D(4,0)),

				Move(INSERT, Vector2D(0,1)),
				Move(INSERT, Vector2D(1,1)),
				Move(INSERT, Vector2D(2,1)),
				Move(INSERT, Vector2D(3,1)),
				Move(INSERT, Vector2D(4,1)),

				Move(INSERT, Vector2D(0,2)),
				Move(INSERT, Vector2D(1,2)),
				Move(INSERT, Vector2D(2,2)),
				Move(INSERT, Vector2D(3,2)),
				Move(INSERT, Vector2D(4,2)),

				Move(INSERT, Vector2D(0,3)),
				Move(INSERT, Vector2D(1,3)),
				Move(INSERT, Vector2D(2,3)),
				Move(INSERT, Vector2D(3,3)),
				Move(INSERT, Vector2D(4,3)),
			};
			int moveCount = 0;
			function<void (Move&)> getMove = [&] (Move& move) -> void{
				Move excpected = moves[moveCount];
				Assert::IsTrue(move == excpected);
				moveCount++;
			};
			for_each(resultMax->begin(), resultMax->end(), getMove);
			moveCount = 0;
			for_each(resultMin->begin(), resultMin->end(), getMove);
			
		};
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

				Assert::IsFalse(illegalMove == move, L"Found illegal move as specified by rule amendment");
			}

			delete legalMoves;
			delete board;
		}
	};
}