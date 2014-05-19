
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
	TEST_CLASS(AbsoluteRelativeConverter) {
	private:
		Board* board;
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
		}

		TEST_METHOD_CLEANUP(DeleteBoard) {
			delete board;
		}

		TEST_METHOD(TopLeftIsRelativeCellNotTileX) {
			Move move = Move(STEP,Vector2D(0,3), Vector2D(-1,3), Vector2D(4,3));
			board->ExecuteMove(move,Max);
			Assert::IsTrue(board->GetRelativeCellAt(Vector2D(0)).GetAbsolutePosition() == Vector2D(19,0));
		}
		TEST_METHOD(TopLeftIsRelativeCellNotTileY) {
			Move move = Move(STEP,Vector2D(4,0), Vector2D(4,-1), Vector2D(4,3));
			board->ExecuteMove(move,Max);
			Assert::IsTrue(board->GetRelativeCellAt(Vector2D(0)).GetAbsolutePosition() == Vector2D(0,19));
		}

		TEST_METHOD(LeftColumnDoesNotMoveToRightWhenNoPiecesOnLeftColumn) {
			Board* board = Board::CreateBoard(
				"2,3,5,1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,\n"
				"3,3,1,5,1,2,0,0,0,0,0,0,0,0,0,0,0,0,2,1,\n"
				"3,3,7,1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,\n"
				"3,3,5,5,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"0,2,6,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"0,6,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n",
				Vector2D(19, 0)
			);
			// This move should not move the topleft of the board. If the relative
			// conversion works fine, the topleft will be an empty place (not a tile).
			// If the relative conversion doesn't work, the topleft will be an empty tile.
			Move move(STEP, Vector2D(0, 1), Vector2D(1, 1));
			board->ExecuteMove(move, Min);
			RelativeCell shouldBeEmptyCell = board->GetRelativeCellAt(Vector2D(0, 0));
			Assert::IsTrue(shouldBeEmptyCell.HasTile(),
				L"Topleft should be empty, but was not! (possible wrong topleft)");
		}
	};
}
