#include <vector>
#include "CppUnitTest.h"
#include "ComputerPlayer.h"
#include "ComputerPlayerAB.h"
#include "StubBoard.h"
#include "StubStaticEval.h"
#include "MoveUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(Minimax) {
	public:
		TEST_METHOD(MiniMaxUnoptimized_ReturnsTrue) {
			IBoard* board = new StubBoard();
			ComputerPlayer* ai = new ComputerPlayer(board, 4);
			int results[81] = {
				64, 32, 74, 29, 40,  9,  7, 14, 21, 11, 70,  8, 16,
				57, 28, 36, 89, 12, 45, 50, 19, 15,  2, 65, 46, 78,
				39, 33, 62, 38, 73, 99, 90, 53, 49, 68, 61, 76, 81,
				24,  1, 95, 59,  5, 44, 34, 54, 60, 77, 56, 92, 51,
				80, 43, 13, 10, 86, 26, 94, 100,18, 79, 85, 48, 96,
				30, 27, 71, 87, 17, 37,  4, 20,  6, 25, 82,  3, 47,
				93, 31, 98
			};
			StubStaticEval* staticEval = new StubStaticEval(results, 81);

			ai->SetEvaluator(staticEval);
			Move move = ai->GetBestMove(Max);
			Assert::IsFalse(move.GetToCell() == Vector2D(-1), L"Returned move is invalid");
			Assert::IsTrue(IsLegalMove(board, move, Max), L"Returned move is not legal on the board");
			Assert::IsTrue(MovesAreEqual(move, Move(STEP, Vector2D(0), Vector2D(1, 0))), L"Returned not the expected move");
			Assert::AreEqual(81, staticEval->GetCallCount(), L"Invalid amount of states have been checked");

			delete board;
			delete ai;
		}

		TEST_METHOD(MiniMax_BothCutOff_ReturnsTrue) {
			IBoard* board = new StubBoard(true);
			ComputerPlayerAB* ai = new ComputerPlayerAB(board, 4);
			int results[7] = {
			// Corrected output based on cut off
				 3, 17,  2, 15, 15,  2,  3,
			};
			StubStaticEval* staticEval = new StubStaticEval(results, 7);

			ai->SetEvaluator(staticEval);
			Move move = ai->GetBestMove(Max);
			Assert::IsFalse(move.GetToCell() == Vector2D(-1), L"Returned move is invalid");
			Assert::IsTrue(IsLegalMove(board, move, Max), L"Returned move is not legal on the board");
			Assert::IsTrue(MovesAreEqual(move,Move(STEP, Vector2D(0), Vector2D(0, 1))), L"Returned not the expected move");
			Assert::AreEqual(7, staticEval->GetCallCount(), L"Invalid amount of states have been checked");

			delete board;
			delete ai;
		}

		TEST_METHOD(MiniMax_MaxNodeCutOff_ReturnsTrue) {
			IBoard* board = new StubBoard(true);
			ComputerPlayerAB* ai = new ComputerPlayerAB(board, 4);
			int results[14] = {
			// Corrected output based on cut off
				3, 17, 4, 12, 1, 1, 25,
				0,  2, 5,  4, 3, 4, 14
			};
			StubStaticEval* staticEval = new StubStaticEval(results, 14);

			ai->SetEvaluator(staticEval);
			Move move = ai->GetBestMove(Max);
			Assert::IsFalse(move.GetToCell() == Vector2D(-1), L"Returned move is invalid");
			Assert::IsTrue(IsLegalMove(board, move, Max), L"Returned move is not legal on the board");
			Assert::IsTrue(MovesAreEqual(move,Move(STEP, Vector2D(0), Vector2D(1, 0))), L"Returned not the expected move");
			Assert::AreEqual(14, staticEval->GetCallCount(), L"Invalid amount of states have been checked");

			delete board;
			delete ai;
		}

		TEST_METHOD(MiniMax_MinNodeCutOff_ReturnsTrue) {
			IBoard* board = new StubBoard(true);
			ComputerPlayerAB* ai = new ComputerPlayerAB(board, 4);
			int results[14] = {
			// Corrected output based on cut off
				3, 17, 2, 1,  1, 25,  0,
				2,  5, 3, 3,  2, 14,  2
			};
			StubStaticEval* staticEval = new StubStaticEval(results, 14);

			ai->SetEvaluator(staticEval);
			Move move = ai->GetBestMove(Max);
			Assert::IsFalse(move.GetToCell() == Vector2D(-1), L"Returned move is invalid");
			Assert::IsTrue(IsLegalMove(board, move, Max), L"Returned move is not legal on the board");
			Assert::IsTrue(MovesAreEqual(move,Move(STEP, Vector2D(0), Vector2D(0, 1))), L"Returned not the expected move");
			Assert::AreEqual(14, staticEval->GetCallCount(), L"Invalid amount of states have been checked");

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