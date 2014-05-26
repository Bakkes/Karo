
#include "ZobristHashing.h"

namespace engine{

	ZobristHashing::ZobristHashing(IBoard* board) {
		_board = board;

		srand((unsigned)time(NULL));
	
		for(int cellValue = 0; cellValue < 16; cellValue++) {
			for(int position = 0; position < 400; position++) {
				_hashValues[cellValue][position] = rand() % 50000;
			}
		}

		// Initialize the hash to the default board representation
		for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 4; y++) {
				_currentHash ^= _hashValues[HasTile][GetCellPosition(Vector2D(x, y))];
			}
		}
	}

	ZobristHashing::~ZobristHashing() {
	}

	void ZobristHashing::ExecuteMove(const Move&) {
	}

	void ZobristHashing::UndoMove(const Move&) {
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
		return position.Y() * 20 + position.X();
	}

	int ZobristHashing::GetHash() const {
		return _currentHash;
	}

}
