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
			STARTING_HASH.set("6552728287026754046102350281149604727769330905160373270568066963872038531116564983417431651535672218946116114284775302700213640827334961587252900996365843522156723072548568344988934820059720782285255043970429150393064085871983973281605978670979583107261753332924612176768911914909606025491141364192950870265989376305388483201310924842889786339194369861070417529782522219633951697830304735416545128147452761735395114778180970753598925143479034882115347686595079409697114107521262824962242411725523383451720008228668718874544811427066618894745705030633616210853810555239854476873468935349495400730222659010518243225182073135852566900685360468194655344271524641094242031025134923051766301143609532643762068490315168909781850465261437649809394373611316849428252709050636514504401346959973410121306357587287009587442574586871654743555052802541408622025360299833015552736060541413950892928255758318436551241465024162783678529424103905684293147140903725156845163741709710723690352138100355046078603302601984068093588482128624010553502595359261632638523299066648911589238455806689033926083011032067968772226518691035608794928419524043381999932375962347906013212744162871871916474485546934929086423609171397181072786014653353036714522600320549099790449545633817961196620687921873753847653488068811314060869413394936218823353693782022208401293020603116510132443466776419137499790943665621607374550808348432134583406799797129092645069272748831828859177165881696478251110443787985528645666984908147930707111901179116568149841779290207009425105501709971412455309644189036761966960194089702077217494459555577274999485091243903495842308055351945520245311600359689137041866696037119435739603262610963594375981924301232481975688989266047350328113665885510035663263571551852698072703644628987537987156307991022366712647207790710916\0", 10);

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

			const char* yolo = hash.ToString();

			bool b = STARTING_HASH == hash;

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
