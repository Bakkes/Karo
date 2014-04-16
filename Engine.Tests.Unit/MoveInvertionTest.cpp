
#include "CppUnitTest.h"
#include "ComputerPlayer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(MoveInvertionTest) {
	public:
		TEST_METHOD(InvertSimpleMove) {
			Move move = Move(MOVE, Vector2D(3, 4), Vector2D(3, 5));
			Move invertedMove = Move(MOVE, Vector2D(3, 5), Vector2D(3, 4));
			Assert::IsTrue(MovesAreEqual(invertedMove, InvertMove(move)));
		}

		TEST_METHOD(InvertBoardChangingMove) {
			Move move = Move(MOVE, Vector2D(3, 4), Vector2D(3, 5), Vector2D(1, 2));
			Move invertedMove = Move(MOVE, Vector2D(1, 2), Vector2D(3, 4), Vector2D(3, 5));
			Assert::IsTrue(MovesAreEqual(invertedMove, InvertMove(move)));
		}

		TEST_METHOD(InvertSimpleJump) {
			Move move = Move(JUMP, Vector2D(3, 4), Vector2D(3, 6));
			Move invertedMove = Move(JUMP, Vector2D(3, 6), Vector2D(3, 4));
			Assert::IsTrue(MovesAreEqual(invertedMove, InvertMove(move)));
		}

		TEST_METHOD(InvertBoardChangingJump) {
			Move move = Move(JUMP, Vector2D(3, 4), Vector2D(3, 6), Vector2D(1, 2));
			Move invertedMove = Move(JUMP, Vector2D(1, 2), Vector2D(3, 4), Vector2D(3, 6));
			Assert::IsTrue(MovesAreEqual(invertedMove, InvertMove(move)));
		}

		TEST_METHOD(InvertInsertion) {
			Move move = Move(INSERT, Vector2D(3, 4));
			Move invertedMove = Move(DELETE, Vector2D(3, 4));
			Assert::IsTrue(MovesAreEqual(invertedMove, InvertMove(move)));
		}

private:
	bool MovesAreEqual(Move moveA, Move moveB) {
		if (moveA.GetMoveType() != moveB.GetMoveType())
			return false;

		if (moveA.GetFromTile() != moveB.GetFromTile())
			return false;

		if (moveA.GetToTile() != moveB.GetToTile())
			return false;

		if (moveA.HasUsedTile() != moveB.HasUsedTile())
			return false;

		if (moveA.GetUsedTile() != moveB.GetUsedTile())
			return false;

		return true;
	}
	};
}