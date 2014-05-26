#include <time.h>
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
				UpdateHash(Vector2D(x, y), 0, HasTile);
			}
		}
	}

	ZobristHashing::~ZobristHashing() {
	}

	void ZobristHashing::ExecuteMove(const Move& move, Players player) {
		switch (move.GetMoveType()) {
		case INSERT:
			InsertPiece(move.GetToCell(), player);
			break;

		case STEP:
			if (move.HasUsedCell()) {
				MoveTile(move.GetUsedCell(), move.GetToCell());
			}
			
			MovePiece(move.GetFromCell(), move.GetToCell());
			break;
		case JUMP:
			if (move.HasUsedCell()) {
				MoveTile(move.GetUsedCell(), move.GetToCell());
			}

			MovePiece(move.GetFromCell(), move.GetToCell());
			break;
		}
	}

	void ZobristHashing::UndoMove(const Move& move, Players player) {
		switch (move.GetMoveType()) {
		case INSERT:
			RemovePiece(move.GetToCell());
			break;

		case STEP:
			if (move.HasUsedCell()) {
				MoveTile(move.GetToCell(), move.GetFromCell());
			}
		
			MovePiece(move.GetToCell(), move.GetFromCell());
			break;
		case JUMP:
			if (move.HasUsedCell()) {
				MoveTile(move.GetToCell(), move.GetFromCell());
			}
		
			MovePiece(move.GetToCell(), move.GetFromCell());
			break;
		}
	}

	void ZobristHashing::UpdateHash(Vector2D position, int cellValue) {
		UpdateHash(position, GetCellData(position), cellValue);
	}

	void ZobristHashing::UpdateHash(Vector2D position, int oldCellValue, int cellValue) {
		int positionIndex = GetCellPosition(position);
		_currentHash ^= _hashValues[oldCellValue][positionIndex];
		_currentHash ^= _hashValues[cellValue][positionIndex];
	}

	void ZobristHashing::InsertPiece(Vector2D position, Players player) {
		int data = HasTile;
		data |= (player == Max) ? IsMax : 0;
		UpdateHash(position, 0, data);
	}

	void ZobristHashing::RemovePiece(Vector2D position) {
		UpdateHash(position, HasTile);
	}

	void ZobristHashing::JumpPiece(Vector2D from, Vector2D to) {
		int cellValue = GetCellData(from) ^ IsFlipped;
		UpdateHash(from, HasTile);
		UpdateHash(to, cellValue);
	}

	void ZobristHashing::MovePiece(Vector2D from, Vector2D to) {
		int cellValue = GetCellData(from);
		UpdateHash(from, HasTile);
		UpdateHash(to, cellValue);
	}

	void ZobristHashing::MoveTile(Vector2D from, Vector2D to) {
		UpdateHash(from, 0);
		UpdateHash(to, HasTile);
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

	int ZobristHashing::GetHash() const {
		return _currentHash;
	}

}
