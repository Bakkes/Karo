#include "ZobristHashing.h"

namespace engine{

	ZobristHashing::ZobristHashing(IBoard* board, IRng* rand) {
		_board = board;
	
		for(int cellValue = 0; cellValue < 16; cellValue++) {
			for(int position = 0; position < 400; position++) {
				_hashValues[cellValue][position] = rand->NextInteger();
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

	int ZobristHashing::GetHash() {
		int hash = 0;
		for (int x = 0; x < 20; ++x) {
			for (int y = 0; y < 20; ++y) {
				const Vector2D position = Vector2D(x, y);
				int cellData = GetCellData(position);
				if (cellData == 0) {
					// This cell is completely empty
					continue;
				}

				hash ^= _hashValues[cellData][GetCellPosition(Vector2D(x, y))];
			}
		}

		return hash;
	}

}
