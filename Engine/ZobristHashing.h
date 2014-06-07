#pragma once

#include "Board.h"
#include "IHashAlgorithm.h"
#include "BigInteger.h"

namespace engine {
	class ENGINE_API ZobristHashing : public IHashAlgorithm {

	public:
		ZobristHashing(IBoard* board);
		~ZobristHashing() override;

		BigInteger GetHash() override;
		void UpdateBoard(IBoard* board) override;

	private:
		BigInteger _hashValues[16][400];
		IBoard* _board;

		int GetCellPosition(const Vector2D& position);
		int GetCellData(const Vector2D& position);

	};
}