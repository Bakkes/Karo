
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
	TEST_CLASS(BoardRelativity) {
	private:
		Board* board;
		Move* move;
	public:
		TEST_METHOD_INITIALIZE(CreateBoard) {
			board = Board::CreateBoard(
				"5,3,3,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,5,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"5,5,1,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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

		TEST_METHOD(WrapBoardChainXTest) {
			move = new Move(STEP, Vector2D(0,0), Vector2D(-1,0), Vector2D(4,3));
			board->ExecuteMove(move, Max);
			board->ExecuteMove(move, Max);
			string result = board->ToString();
			Assert::IsTrue(
				"7,3,3,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,5,7,\n"
				"3,5,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"5,5,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				==
				result
			);
		};
		TEST_METHOD(WrapBoardChainYTest) {
			move = new Move(STEP, Vector2D(0,0), Vector2D(0,-1), Vector2D(4,3));
			board->ExecuteMove(move, Max);
			board->ExecuteMove(move, Max);
			string result = board->ToString();
			Assert::IsTrue(
				"7,3,3,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,5,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"5,5,1,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				==
				result
			);
		};
		TEST_METHOD(WalkAroundTest) {
			move = new Move(STEP, Vector2D(0,0), Vector2D(0,-1), Vector2D(4,3));
			board->ExecuteMove(move, Max);
			board->ExecuteMove(move, Max);
			move = new Move(STEP, Vector2D(0,0), Vector2D(0,1));
			board->ExecuteMove(move, Max);
			move = new Move(STEP, Vector2D(0,1), Vector2D(1,1), Vector2D(3,5));
			board->ExecuteMove(move, Max);
			string result = board->ToString();
			Assert::IsTrue(
				"7,3,3,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,5,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"5,5,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"7,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				==
				result
			);
		}
		TEST_METHOD(TopLeftMovement) {
			board = Board::CreateBoard( 
				"7,3,3,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,5,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"5,5,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"7,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n",
				Vector2D(0,18)
			);
			move = new Move(STEP, Vector2D(1,1), Vector2D(2,1), Vector2D(0,0));
			board->ExecuteMove(move, Max);
			move = new Move(STEP, Vector2D(2,0), Vector2D(3,0), Vector2D(0,0));
			board->ExecuteMove(move, Max);
			string result = board->ToString();
			OutputDebugString(result.c_str());
			Assert::IsTrue(
				"7,3,3,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,5,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"5,5,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"6,7,7,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				==
				result
			);
		}
		TEST_METHOD(GetRelativeCellChangedTopLeft) {
			move = new Move(STEP, Vector2D(0,0), Vector2D(-1,0), Vector2D(4,3));
			board->ExecuteMove(move, Max);
			board->ExecuteMove(move, Max);
			string result = board->ToString();
			Assert::IsTrue(board->GetRelativeCellAt(Vector2D(0,0)).GetAbsolutePosition() == Vector2D(18,0));

		}
	};
}
