
#include "CppUnitTest.h"
#include "Board.h"
#include "RelativeCell.h"
#include <string>
#include <iostream>
#include "Windows.h"
#include "ComputerPlayerMO.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;
using namespace std;
namespace Tests {
	TEST_CLASS(BoardTests) {
	private:
		Board* board;
		string standartBoard;
	public:
		TEST_METHOD_INITIALIZE(CreateBoard) {
			board = new Board();
			standartBoard = "3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n";
		}

		TEST_METHOD_CLEANUP(DeleteBoard) {
			delete board;
		}

		TEST_METHOD(TestGetRelativeTileEdgeCase) {
			Vector2D input = Vector2D(19,2);
			board = Board::CreateBoard(
				"3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,6,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,5,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n",
				input);
			Assert::IsTrue(board->GetRelativeCellAt(Vector2D(0,0)).GetAbsolutePosition() == input);
			Assert::IsTrue(board->GetRelativeCellAt(Vector2D(0,0)).GetData() == 3);
		}
		TEST_METHOD(ConstructorIsGoodSize) {
			/** the board should be constructed as a empty 5*4*/
			string result = board->ToString();
			// asuming a 1 marks a tile present and a 2 marks that the tile is empty
			Assert::IsTrue(standartBoard == result);
			// Note: I don't realy get why there are only 19 lines, but when I change comparision
			// in the grid all hell breaks loose, so I just ignore this suspcicion for now
		}
		TEST_METHOD(IdemPotentForCreateBoardAndToString) {
			board = Board::CreateBoard(standartBoard);
			string result = board->ToString();
			Assert::IsTrue(result == standartBoard);
		}

		TEST_METHOD(TestGetRelativeTile) {
			Vector2D input = Vector2D(3,2);
			board = Board::CreateBoard(
				standartBoard,
				input);
			Vector2D result = board->GetRelativeCellAt(Vector2D(0,0)).GetAbsolutePosition();
			Assert::IsTrue(result == input);
		}

		TEST_METHOD(WrapArroundTopLeft) {
			Vector2D input = Vector2D(0);
			RelativeCell result = board->GetRelativeCellAt(input);
			Assert::IsTrue(
				result.GetAbsolutePosition()
					== 
				input
			);
			Assert::IsTrue(
				result.GetLeft().GetAbsolutePosition()
					== 
				Vector2D(19,0)
			);
			Assert::IsTrue(
				result.GetTop().GetAbsolutePosition()
					== 
				Vector2D(0,19)
			);
		}
		TEST_METHOD(WrapArroundBottomRight) {
			Vector2D input = Board::initSize; // i want the outer most absolute postion
			board = Board::CreateBoard(
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
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,\n"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,\n",
				Vector2D(14, 15) // set the absolute topleft
			);
			RelativeCell result = board->GetRelativeCellAt(input);
			Assert::IsTrue(
				result.GetAbsolutePosition()
					== 
				Vector2D(19,19)
			);
			Assert::IsTrue(
				result.GetRight().GetAbsolutePosition()
					== 
				Vector2D(0,19)
			);
			Assert::IsTrue(
				result.GetBottom().GetAbsolutePosition()
					== 
				Vector2D(19,0)
			);
		}

		TEST_METHOD(MoreThanOneCharlenNumberTest) {
			string input = string(
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n");
			board = Board::CreateBoard(input);
			string result = board->ToString();

			Assert::IsTrue(result == input);
		}
		TEST_METHOD(IsInitialBoardEmpty) {
			vector<RelativeCell>* result = board->GetOccupiedTiles();
			Assert::IsTrue(*result == vector<RelativeCell>());
			delete result;
		};

		TEST_METHOD(CountEgesTest) {
			Assert::IsTrue(board->CountNonDiagonalEdges(board->GetRelativeCellAt(Vector2D(0,0))) == 2);
			Assert::IsTrue(board->CountNonDiagonalEdges(board->GetRelativeCellAt(Vector2D(0,3))) == 2);
			Assert::IsTrue(board->CountNonDiagonalEdges(board->GetRelativeCellAt(Vector2D(4,0))) == 2);
			Assert::IsTrue(board->CountNonDiagonalEdges(board->GetRelativeCellAt(Vector2D(4,3))) == 2);
			Assert::IsTrue(board->CountNonDiagonalEdges(board->GetRelativeCellAt(Vector2D(3,3))) == 3);
			Assert::IsTrue(board->CountNonDiagonalEdges(board->GetRelativeCellAt(Vector2D(3,2))) == 4);
		}

		TEST_METHOD(BoardDoMoveThenUndoMoveDoesNotScrewBoardUp) {
			Board* board = Board::CreateBoard(
				"2,3,5,1,5,2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,\n"
				"1,3,1,5,1,2,0,0,0,0,0,0,0,0,0,0,0,0,2,3,\n"
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
			Move evilMove(STEP, Vector2D(3, 0), Vector2D(3, -1), Vector2D(0, 1));
			board->ExecuteMove(evilMove, Max);
			board->UndoMove(evilMove, Max);
			RelativeCell shouldBeEmptyCell = board->GetRelativeCellAt(Vector2D(1, 0));
			OutputDebugString(board->ToString().c_str());
			Assert::IsFalse(shouldBeEmptyCell.HasTile());
		}
		TEST_METHOD(BoardALotOfMovesTest) {
			Board* board = new Board();
			board->ExecuteMove(Move(INSERT, Vector2D(3, 0), Vector2D(3, 0)), Min);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(2, 3)), Max);
			board->ExecuteMove(Move(INSERT, Vector2D(2, 0), Vector2D(2, 0)), Min);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(3, 1)), Max);
			board->ExecuteMove(Move(INSERT, Vector2D(1, 0), Vector2D(1, 0)), Min);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(3, 3)), Max);
			board->ExecuteMove(Move(INSERT, Vector2D(2, 2), Vector2D(2, 2)), Min);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(0, 2)), Max);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(0, 0)), Min);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(4, 1)), Max);
			board->ExecuteMove(Move(INSERT, Vector2D(4, 0), Vector2D(4, 0)), Min);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(0, 1)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(0, 0), Vector2D(1, -1)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(0, 2), Vector2D(0, 1)), Max);
			board->ExecuteMove(Move(JUMP, Vector2D(3, 1), Vector2D(5, 1)), Min);
			board->ExecuteMove(Move(JUMP, Vector2D(2, 4), Vector2D(4, 4)), Max);
			board->ExecuteMove(Move(JUMP, Vector2D(1, 1), Vector2D(3, 1)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(0, 3), Vector2D(-1, 2)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(2, 0), Vector2D(3, 0)), Min);
			board->ExecuteMove(Move(JUMP, Vector2D(5, 4), Vector2D(3, 4)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(3, 1), Vector2D(2, 2)), Min);
			board->ExecuteMove(Move(JUMP, Vector2D(0, 2), Vector2D(2, 0)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(6, 1), Vector2D(6, 2)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(0, 1), Vector2D(-1, 2)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(6, 2), Vector2D(6, 1)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(3, 4), Vector2D(4, 5)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(5, 1), Vector2D(6, 2)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(4, 4), Vector2D(5, 4)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(2, 2), Vector2D(1, 2)), Min);
			board->ExecuteMove(Move(JUMP, Vector2D(4, 5), Vector2D(6, 3)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(6, 1), Vector2D(7, 1)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(2, 0), Vector2D(3, 1)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(6, 2), Vector2D(5, 3)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(5, 2), Vector2D(6, 1)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(5, 3), Vector2D(4, 3)), Min);
			board->ExecuteMove(Move(JUMP, Vector2D(3, 1), Vector2D(5, 1)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(4, 1), Vector2D(3, 1)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(6, 3), Vector2D(7, 3)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(1, 2), Vector2D(1, 1)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(5, 1), Vector2D(4, 1)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(4, 3), Vector2D(3, 2)), Min);
			board->ExecuteMove(Move(JUMP, Vector2D(4, 1), Vector2D(4, 3)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(3, 2), Vector2D(2, 2)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(6, 1), Vector2D(6, 2)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(1, 1), Vector2D(1, 2)), Min);
			board->ExecuteMove(Move(JUMP, Vector2D(4, 3), Vector2D(2, 3)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(3, 1), Vector2D(4, 1)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(4, 2), Vector2D(5, 3)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(2, 2), Vector2D(3, 1)), Min);
			board->ExecuteMove(Move(JUMP, Vector2D(0, 2), Vector2D(2, 2)), Max);
			board->ExecuteMove(Move(JUMP, Vector2D(3, 1), Vector2D(5, 1)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(2, 2), Vector2D(2, 1)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(2, 0), Vector2D(2, 1)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(1, 3), Vector2D(2, 4)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(0, 1), Vector2D(1, 2)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(2, 3), Vector2D(2, 4)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(3, 0), Vector2D(4, 0)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(4, 1), Vector2D(3, 0)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(5, 0), Vector2D(4, 1)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(0, 0), Vector2D(0, -1)), Max);
			board->ExecuteMove(Move(STEP, Vector2D(1, 3), Vector2D(2, 2)), Min);
			board->ExecuteMove(Move(STEP, Vector2D(0, 0), Vector2D(0, 1)), Max);
			int len = board->GetOccupiedTiles()->size() + board->GetEmptyTiles()->size();
			OutputDebugString(board->ToString().c_str());
			Assert::AreEqual(20, len);
		}

		TEST_METHOD(DontInsertTooEarly) {			
			Board* board = new Board();
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(2, 1)), Max);
			board->ExecuteMove(Move(INSERT, Vector2D(4, 3), Vector2D(4, 3)), Min);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(2, 3)), Max);
			board->ExecuteMove(Move(INSERT, Vector2D(1, 0), Vector2D(1, 0)), Min);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(3, 0)), Max);
			board->ExecuteMove(Move(INSERT, Vector2D(1, 1), Vector2D(1, 1)), Min);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(3, 1)), Max);
			board->ExecuteMove(Move(INSERT, Vector2D(1, 2), Vector2D(1, 2)), Min);
			board->ExecuteMove(Move(INSERT, Vector2D(0, 0), Vector2D(3, 2)), Max);
			board->ExecuteMove(Move(INSERT, Vector2D(4, 0), Vector2D(4, 0)), Min);
			ComputerPlayerMO* cp = new ComputerPlayerMO(board, 3);
			Move bm = cp->GetBestMove(Max);
			Assert::IsTrue(bm.GetMoveType() == INSERT);

		}
	};
		
}
