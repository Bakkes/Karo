
#include "CppUnitTest.h"
#include "ComputerPlayer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(MoveInvertionTest) {
	public:
		TEST_METHOD(InvertSimpleMove) {
			Move move = Move(MoveType::MOVE, 1, 2, MoveDirection::NONE, -1);
			Move invertedMove = InvertMove(move);
			Assert::IsTrue(MovesAreEqual(invertedMove, Move(MoveType::MOVE, 2, 1, MoveDirection::NONE, -1)));
		}

		TEST_METHOD(InvertSimpleJump) {
			Move move = Move(MoveType::JUMP, 1, 2, MoveDirection::NONE, -1);
			Move invertedMove = InvertMove(move);
			Assert::IsTrue(MovesAreEqual(invertedMove, Move(MoveType::JUMP, 2, 1, MoveDirection::NONE, -1)));
		}

		TEST_METHOD(InvertInsertion) {
			Move move = Move(MoveType::INSERT, -1, 2, MoveDirection::NONE, -1);
			Move invertedMove = InvertMove(move);
			Assert::IsTrue(MovesAreEqual(invertedMove, Move(MoveType::DELETE, -1, 2, MoveDirection::NONE, -1)));
		}

private:
	bool MovesAreEqual(Move moveA, Move moveB) {
		if (moveA.GetMoveType() != moveB.GetMoveType())
			return false;

		if (moveA.GetEmptyTile() != moveB.GetEmptyTile())
			return false;

		if (moveA.GetFromTile() != moveB.GetFromTile())
			return false;

		if (moveA.GetToTile() != moveB.GetToTile())
			return false;

		if (moveA.GetMoveDirection() != moveB.GetMoveDirection())
			return false;

		return true;
	}
	};
}