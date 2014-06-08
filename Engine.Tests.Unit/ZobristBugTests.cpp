#include <CppUnitTest.h>
#include <map>
#include "Board.h"
#include "ZobristHashing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {
	TEST_CLASS(ZobristBugTests) {
		// Tests for collisions by calculating the hash of a lot of boards.
		// If we calculate the same hash for two different board states,
		// the test will fail.
		TEST_METHOD(TestForCollisions) {
			// How many moves will the engine perform to check for collisions.
			// Higher values will give better results, but make the test slower.
			const int Iterations = 200;

			// Key: Sane board string.
			// Value: Zobrist hash value.
			std::map<engine::BigInteger, std::string> hashes;
			engine::Board board;
			engine::ZobristHashing zobrist(&board);
			engine::Players currentPlayer = engine::Max;

			for (int i = 0; i < Iterations; i++) {
				auto legalMoves = board.GetLegalMoves(currentPlayer);
				board.ExecuteMove(legalMoves[rand() % legalMoves.size()], currentPlayer);

				std::string saneString = board.ToSaneString();
				engine::BigInteger hash = zobrist.GetHash();

				auto it = hashes.find(hash);
				if (it == hashes.end()) {
					hashes.insert(std::pair<engine::BigInteger, std::string>(hash, saneString));
				} else {
					Assert::AreEqual(saneString, it->second,
						L"Zobrist hash collision found!");
				}

				// Swap player.
				if (currentPlayer == engine::Max) {
					currentPlayer = engine::Min;
				} else {
					currentPlayer = engine::Max;
				}
			}
		}
	};
}