#include "ZobristHashing.h"

namespace engine{

	ZobristHashing::ZobristHashing(IBoard* board) {
		_board = board;

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

	ZobristHashing::~ZobristHashing() {
	}

	int ZobristHashing::GetCellData(const Vector2D& position) {
		RelativeCell cell = _board->GetRelativeCellAt(position);

		if (!cell.HasTile())
			return 0;

		if (cell.IsEmpty()) {
			return HasTile | IsEmpty;
		}

		int data = HasTile;

		if (cell.IsFlipped()) {
			data |= IsFlipped;
		}

		if (cell.IsMaxPiece()) {
			data |= IsMax;
		}
		
		return data;
	}

	int ZobristHashing::GetCellPosition(const Vector2D& position) {
		return (int)position.Y() * 20 + (int)position.X();
	}

	void ZobristHashing::UpdateBoard(IBoard* board) {
		this->_board = board;
	}

	BigInteger ZobristHashing::GetHash() {
		BigInteger hash(0);

		for (int x = 0; x < 20; ++x) {
			for (int y = 0; y < 20; ++y) {
				const Vector2D position = Vector2D(x, y);
				int cellData = GetCellData(position);
				if (cellData == 0) {
					// This cell is completely empty
					continue;
				}

				hash = hash ^ _hashValues[cellData][GetCellPosition(Vector2D(x, y))];
			}
		}

		return hash;
	}

}
