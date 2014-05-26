
#include "ZobristHashing.h"

namespace engine{

	ZobristHashing::ZobristHashing(IBoard* board) {
		_board = board;

		srand((unsigned)time(NULL));
	
		for(int cellValue = 0; cellValue < 16; cellValue++) {
			for(int position = 0; position < 400; position++) {
				_hashValues[cellValue][position] = rand() % 1000;
			}
		}
		// TODO Initialize the hash with the default board layout!
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
