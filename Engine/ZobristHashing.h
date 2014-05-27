#pragma once

#include "Board.h"
#include "IHashAlgorithm.h"
#include "IRng.h"

namespace engine {
	class ENGINE_API ZobristHashing : public IHashAlgorithm {

	public:
		ZobristHashing(IBoard* board, IRng* rand);
		virtual ~ZobristHashing();

		void ExecuteMove(const Move&, Players player) override;
		void UndoMove(const Move&, Players player) override;

		int GetHash() const override;

	private:
		int _hashValues[16][400];
		int _currentHash;
		IBoard* _board;
		IRng* _rand;

		int GetCellPosition(const Vector2D& position);
		int GetCellData(const Vector2D& position);
		
		void UpdateHash(Vector2D position, int cellValue);
		void UpdateHash(Vector2D position, int cellOldValue, int cellValue);

		void InsertPiece(Vector2D position, Players player);
		void RemovePiece(Vector2D position);
		void MovePiece(Vector2D from, Vector2D to);
		void JumpPiece(Vector2D from, Vector2D to);
		void MoveTile(Vector2D from, Vector2D to);
	};
}