#pragma once

#include "Board.h"
#include "IHashAlgorithm.h"
#include "IRng.h"

namespace engine {
	class ENGINE_API ZobristHashing : public IHashAlgorithm {

	public:
		ZobristHashing(IBoard* board, IRng* rand);
		~ZobristHashing() override;

		long long GetHash() override;
		void UpdateBoard(IBoard* board) override;
		void ExecuteMove(const Move& move) override;
		void UndoMove(const Move& move, Players player) override;

	private:
		long long _hashValues[16][400];
		IBoard* _board;
		long long _hash;

		long long RecaclulateHash();

		int GetDataForPlayer(const Vector2D& position);

		int GetCellPosition(const Vector2D& position);
		int GetCellData(const Vector2D& position);

	};
}