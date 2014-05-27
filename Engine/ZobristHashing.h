#pragma once

#include "Board.h"
#include "IHashAlgorithm.h"
#include "IRng.h"

namespace engine {
	class ENGINE_API ZobristHashing : public IHashAlgorithm {

	public:
		ZobristHashing(IBoard* board, IRng* rand);
		~ZobristHashing() override;

		int GetHash() override;

	private:
		int _hashValues[16][400];
		IBoard* _board;

		int GetCellPosition(const Vector2D& position);
		int GetCellData(const Vector2D& position);

	};
}