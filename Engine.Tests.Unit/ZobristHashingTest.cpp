#include <vector>
#include "CppUnitTest.h"
#include "Board.h"
#include "ZobristHashing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;

namespace Tests {
	TEST_CLASS(ZobristHashingTest) {	
	public:
		TEST_METHOD_INITIALIZE(InitZobristTest) {
			STARTING_HASH.set(4329604);

			const int bits = 5;
	
			for(int cellValue = 1; cellValue <= 16; cellValue++) {
				for(int y = 0; y < 20; y++) {
					for (int x = 0; x < 20; x++) {
						int position = GetCellPosition(Vector2D(x, y));

						_hashValues[cellValue - 1][position].set(cellValue);
						_hashValues[cellValue - 1][position].multiply2exp((y * (20 * 20 * bits)) + (x * bits));
					}
				}
			}
		}

		TEST_METHOD(InitialHash) {
			Board* board = CreateStartingBoard();
			ZobristHashing hasher(board);

			BigInteger hash = hasher.GetHash();

			Assert::IsTrue(STARTING_HASH == hash, L"Invalid Hash");

			delete board;
		}

		TEST_METHOD(HashJumpWithTileMove) {
			Board* board = Board::CreateBoard(
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
			ZobristHashing hasher(board);

			Vector2D from(3, 3);
			Vector2D to(5, 3);
			Vector2D used(0, 0);

			Move move(JUMP, from, to, used);
			board->ExecuteMove(move, Min);

			BigInteger baseHash = STARTING_HASH;
			// Correct the Starting has based on the standard board
			baseHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(from)];
			baseHash ^= _hashValues[HasTile][GetCellPosition(from)];

			BigInteger expectedHash = baseHash;

			// Delete Piece
			expectedHash ^= _hashValues[HasTile][GetCellPosition(from)];
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(from)];

			// Remove tile
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(used)];

			// Insert Piece at new tile
			expectedHash ^= _hashValues[HasTile | IsFlipped][GetCellPosition(to)];

			Assert::IsTrue(expectedHash == hasher.GetHash(), L"Invalid hash after Move");

			board->UndoMove(move, Min);
			Assert::IsTrue(baseHash == hasher.GetHash(), L"Invalid hash after undo");
		}

		TEST_METHOD(HashStepWithTileMoveShiftTL) {
			Board* board = Board::CreateBoard(
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
			ZobristHashing hasher(board);

			Vector2D from(0, 0);
			Vector2D shiftFrom(1, 0);
			Vector2D to(-1, 0);
			Vector2D shiftTo(0, 0);
			Vector2D used(4, 3);
			Vector2D shiftUsed(5, 3);

			Move move(STEP, from, to, used);
			board->ExecuteMove(move, Min);

			BigInteger baseHash = STARTING_HASH;
			// Correct the Starting has based on the standard board
			baseHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(from)];
			baseHash ^= _hashValues[HasTile][GetCellPosition(from)];

			BigInteger expectedHash = 0;

			// Generate board has but shifted
			for (int x = 0; x < 5; ++x) {
				for (int y = 0; y < 4; ++y) {
					expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(Vector2D(x + 1, y))];
				}
			}
			
			// Insert the piece of the player
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(shiftFrom)];
			expectedHash ^= _hashValues[HasTile][GetCellPosition(shiftFrom)];

			// Remove the player
			expectedHash ^= _hashValues[HasTile][GetCellPosition(shiftFrom)];
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(shiftFrom)];

			// Remove the tile
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(shiftUsed)];

			// Insert the player at new tile
			expectedHash ^= _hashValues[HasTile][GetCellPosition(shiftTo)];

			Assert::IsTrue(expectedHash == hasher.GetHash(), L"Invalid hash after Move");

			board->UndoMove(move, Min);
			Assert::IsTrue(baseHash == hasher.GetHash(), L"Invalid hash after undo");
		}

		TEST_METHOD(HashStepWithTileMove) {
			Board* board = Board::CreateBoard(
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
			ZobristHashing hasher(board);

			Vector2D from(3, 3);
			Vector2D to(3, 4);
			Vector2D used(0, 0);

			Move move(STEP, from, to, used);
			board->ExecuteMove(move, Min);

			BigInteger baseHash = STARTING_HASH;
			// Correct the Starting has based on the standard board
			baseHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(from)];
			baseHash ^= _hashValues[HasTile][GetCellPosition(from)];

			BigInteger expectedHash = baseHash;

			// Delete Piece
			expectedHash ^= _hashValues[HasTile][GetCellPosition(from)];
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(from)];

			// Remove tile
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(used)];

			// Insert Piece at new tile
			expectedHash ^= _hashValues[HasTile][GetCellPosition(to)];

			Assert::IsTrue(expectedHash == hasher.GetHash(), L"Invalid hash after Move");

			board->UndoMove(move, Min);
			Assert::IsTrue(baseHash == hasher.GetHash(), L"Invalid hash after undo");
		}

		TEST_METHOD(HashJumpMove) {
			Board* board = Board::CreateBoard(
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
			ZobristHashing hasher(board);

			Vector2D from(3, 3);
			Vector2D to(1, 3);

			Move move(JUMP, from, to);
			board->ExecuteMove(move, Min);

			BigInteger baseHash = STARTING_HASH;
			// Correct the Starting has based on the standard board
			baseHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(from)];
			baseHash ^= _hashValues[HasTile][GetCellPosition(from)];

			BigInteger expectedHash = baseHash;
			
			// Delete Piece at (3, 3)
			expectedHash ^= _hashValues[HasTile][GetCellPosition(from)];
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(from)];

			// Insert Piece at (1, 3)
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(to)];
			expectedHash ^= _hashValues[HasTile | IsFlipped][GetCellPosition(to)];

			Assert::IsTrue(expectedHash == hasher.GetHash(), L"Invalid hash after Move");

			board->UndoMove(move, Min);
			Assert::IsTrue(baseHash == hasher.GetHash(), L"Invalid hash after undo");
		}

		TEST_METHOD(HashStepMove) {
			Board* board = Board::CreateBoard(
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
				"3,3,3,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
			ZobristHashing hasher(board);

			Vector2D from(3, 3);
			Vector2D to(2, 3);

			Move move(STEP, from, to);
			board->ExecuteMove(move, Min);

			BigInteger baseHash = STARTING_HASH;	
			// Correct the Starting has based on the standard board
			baseHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(from)];
			baseHash ^= _hashValues[HasTile][GetCellPosition(from)];

			BigInteger expectedHash = baseHash;

			// Delete Piece at (3, 3)
			expectedHash ^= _hashValues[HasTile][GetCellPosition(from)];
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(from)];

			// Insert Piece at (2, 3)
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(to)];
			expectedHash ^= _hashValues[HasTile][GetCellPosition(to)];

			Assert::IsTrue(expectedHash == hasher.GetHash(), L"Invalid hash after Move");

			board->UndoMove(move, Min);
			Assert::IsTrue(baseHash == hasher.GetHash(), L"Invalid hash after undo");
		}

		TEST_METHOD(HashInsertMove) {
			Board* board = CreateStartingBoard();
			ZobristHashing hasher(board);

			Move move(INSERT, Vector2D(3, 3));
			board->ExecuteMove(move, Min);

			BigInteger expectedHash = STARTING_HASH;
			expectedHash ^= _hashValues[HasTile | IsEmpty][GetCellPosition(Vector2D(3, 3))];
			expectedHash ^= _hashValues[HasTile][GetCellPosition(Vector2D(3, 3))];

			Assert::IsTrue(expectedHash == hasher.GetHash(), L"Invalid hash after Move");

			board->UndoMove(move, Min);
			Assert::IsTrue(STARTING_HASH == hasher.GetHash(), L"Invalid hash after undo");
		}

		int GetCellPosition(const Vector2D& position) {
			return (int)position.Y() * 20 + (int)position.X();
		}

		Board* CreateStartingBoard() {
			return Board::CreateBoard(
				"3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n"
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
				"0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,\n");
		}

		BigInteger _hashValues[16][400];
		BigInteger STARTING_HASH;
	};
}
