#include <vector>
#include "CppUnitTest.h"
#include "StubBoard.h"
#include "StubStaticEval.h"
#include "AIFactory.h"
#include "Board.h"
#include "StaticEvaluation.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(Minimax) {
	private:
		AIFactory* _factory;
	public:
		TEST_METHOD_INITIALIZE(CreateBoard) {
			_factory =new AIFactory(new StubBoard(true),4);
		}
		TEST_METHOD(MiniMaxUnoptimized_ReturnsTrue) {
			AI* ai = _factory->CreateAI();
			((StubBoard*)_factory->GetBoard())->SetMinimalMoves(false);
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
			Assert::IsTrue(IsLegalMove(_factory->GetBoard(), move, Max), L"Returned move is not legal on the board");
			Assert::IsTrue(move == Move(STEP, Vector2D(0), Vector2D(1, 0)), L"Returned not the expected move");
			Assert::AreEqual(81, staticEval->GetCallCount(), L"Invalid amount of states have been checked");

			delete _factory->GetBoard();
			delete ai;
		}

		TEST_METHOD(MiniMax_BothCutOff_ReturnsTrue) {
			AI* ai = _factory->CreateAlfaAI();
			int results[7] = {
			// Corrected output based on cut off
				 3, 17,  2, 15, 15,  2,  3,
			};
			StubStaticEval* staticEval = new StubStaticEval(results, 7);

			ai->SetEvaluator(staticEval);
			Move move = ai->GetBestMove(Max);
			Assert::IsFalse(move.GetToCell() == Vector2D(-1), L"Returned move is invalid");
			Assert::IsTrue(IsLegalMove(_factory->GetBoard(), move, Max), L"Returned move is not legal on the board");
			Assert::IsTrue(move == Move(STEP, Vector2D(0), Vector2D(0, 1)), L"Returned not the expected move");
			int callCount= staticEval->GetCallCount();
			Assert::AreEqual(7, callCount, L"Invalid amount of states have been checked");

			delete _factory->GetBoard();
			delete ai;
		}

		TEST_METHOD(MiniMax_MaxNodeCutOff_ReturnsTrue) {
			AI* ai = _factory->CreateAlfaAI();
			int results[14] = {
			// Corrected output based on cut off
				3, 17, 4, 12, 1, 1, 25,
				0,  2, 5,  4, 3, 4, 14
			};
			StubStaticEval* staticEval = new StubStaticEval(results, 14);

			ai->SetEvaluator(staticEval);
			Move move = ai->GetBestMove(Max);
			Assert::IsFalse(move.GetToCell() == Vector2D(-1), L"Returned move is invalid");
			Assert::IsTrue(IsLegalMove(_factory->GetBoard(), move, Max), L"Returned move is not legal on the board");
			Assert::IsTrue(move == Move(STEP, Vector2D(0), Vector2D(1, 0)), L"Returned not the expected move");
			Assert::AreEqual(14, staticEval->GetCallCount(), L"Invalid amount of states have been checked");

			delete _factory->GetBoard();
			delete ai;
		}

		TEST_METHOD(MiniMax_MinNodeCutOff_ReturnsTrue) {
			AI* ai = _factory->CreateAlfaAI();
			int results[14] = {
			// Corrected output based on cut off
				3, 17, 2, 1,  1, 25,  0,
				2,  5, 3, 3,  2, 14,  2
			};
			StubStaticEval* staticEval = new StubStaticEval(results, 14);

			ai->SetEvaluator(staticEval);
			Move move = ai->GetBestMove(Max);
			Assert::IsFalse(move.GetToCell() == Vector2D(-1), L"Returned move is invalid");
			Assert::IsTrue(IsLegalMove(_factory->GetBoard(), move, Max), L"Returned move is not legal on the board");
			Assert::IsTrue(move == Move(STEP, Vector2D(0), Vector2D(0, 1)), L"Returned not the expected move");
			Assert::AreEqual(14, staticEval->GetCallCount(), L"Invalid amount of states have been checked");

			delete _factory->GetBoard();
			delete ai;
		}
		TEST_METHOD(ThisIsInsertPhaseIntegrationTest) {
			Board* board = Board::CreateBoard(
				"3,5,7,1,1,6,0,0,0,0,0,0,0,0,0,0,0,0,0,6,"
				"7,5,15,1,7,6,0,0,0,0,0,0,0,0,0,0,0,0,0,6,"
				"7,5,5,1,7,6,0,0,0,0,0,0,0,0,0,0,0,0,0,6,"
				"15,5,1,7,7,6,0,0,0,0,0,0,0,0,0,0,0,0,0,6,"
				"6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
				"6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"
			);
			vector<Move> legalMoves = board->GetLegalMoves(Max);
			for(auto it = legalMoves.begin(); it < legalMoves.end(); ++it){
				Assert::IsTrue(it->GetMoveType() == INSERT);
			}
			legalMoves = board->GetLegalMoves(Min);
			for(auto it = legalMoves.begin(); it < legalMoves.end(); ++it){
				Assert::IsTrue(it->GetMoveType() == INSERT);
			}
			AI* ai = AIFactory(board,3).CreateAI();
			ai->SetEvaluator(new StaticEvaluation());
			Move m = ai->GetBestMove(Max);
			Assert::IsTrue(m.GetMoveType() == INSERT);
			m = ai->GetBestMove(Min);
			Assert::IsTrue(m.GetMoveType() == INSERT);
		}

private:
	bool IsLegalMove(IBoard* board, Move move, Players player) {
		std::vector<Move> legalMoves = board->GetLegalMoves(player);
		for (auto it = legalMoves.begin(); it != legalMoves.end(); ++it) {
			if (move == *it) {
				return true;
			}
		}
		
		return false;
	}
	};
}
