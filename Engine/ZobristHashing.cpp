#include "ZobristHashing.h"

namespace engine{

	ZobristHashing::ZobristHashing(IBoard* board, IRng* rand) {
		_board = board;
	
		for(int cellValue = 0; cellValue < 16; cellValue++) {
			for(int position = 0; position < 400; position++) {
				_hashValues[cellValue][position] = rand->NextInteger();
			}
		}

		if (_board != nullptr) {
			// Calculate base hash
			_hash = RecaclulateHash();
		} else {
			_hash = 0;
		}
	}

	ZobristHashing::~ZobristHashing() {
	}

	void ZobristHashing::ExecuteMove(const Move& move) {
		if (move.HasUsedCell()) {
			// This move potentially shifts the TopLeft in our relative field
			// Trying to figure the new hash based on that move is complex
			// Rebasing the hash is faster
			_hash = RecaclulateHash();
			return;
		}

		int positionTo = GetCellPosition(move.GetToCell());
		int positionFrom = GetCellPosition(move.GetFromCell());

		switch (move.GetMoveType()) {
		case INSERT:
			// Remove empty tile
			_hash ^= _hashValues[HasTile | IsEmpty][positionFrom];
			// Insert tile with player
			_hash ^= _hashValues[HasTile | GetDataForPlayer(move.GetToCell())][positionTo];
			break;

		case STEP: {
			int toCellData = GetCellData(move.GetToCell());

			// FROM
			// Remove tile with player
			_hash ^= _hashValues[toCellData][positionFrom];
			// Insert empty tile
			_hash ^= _hashValues[HasTile | IsEmpty][positionFrom];

			// TO
			// Remove empty tile
			_hash ^= _hashValues[HasTile | IsEmpty][positionTo];
			// Insert tile with player
			_hash ^= _hashValues[toCellData][positionTo];
			break;
				   }

		case JUMP: {
			int toCellData = GetCellData(move.GetToCell());

			// FROM
			// Remove tile with player (xor flipped as the board state has already been updated!)
			_hash ^= _hashValues[toCellData ^ IsFlipped][positionFrom];
			// Insert empty tile
			_hash ^= _hashValues[HasTile | IsEmpty][positionFrom];

			// TO
			// Remove empty tile
			_hash ^= _hashValues[HasTile | IsEmpty][positionTo];
			// Insert tile with player
			_hash ^= _hashValues[toCellData][positionTo];

			break;
				   }
		}

	}
	
	void ZobristHashing::UndoMove(const Move& move, Players& player) {
		if (move.HasUsedCell()) {
			// This move potentially shifts the TopLeft in our relative field
			// Trying to figure the new hash based on that move is complex
			// Rebasing the hash is faster
			_hash = RecaclulateHash();
			return;
		}

		int playerValue = (player == Max) ? IsMax : 0;
		int positionTo = GetCellPosition(move.GetToCell());
		int positionFrom = GetCellPosition(move.GetFromCell());

		switch (move.GetMoveType()) {
		case INSERT:
			// Remove the player with tile
			_hash ^= _hashValues[HasTile | playerValue][positionTo];
			// Insert empty tile
			_hash ^= _hashValues[HasTile | IsEmpty][positionTo];
			break;

		case STEP: {
			int cellData = GetCellData(move.GetFromCell());

			// FROM
			// Remove empty tile
			_hash ^= _hashValues[HasTile | IsEmpty][positionFrom];
			// Insert player
			_hash ^= _hashValues[cellData][positionFrom];

			// TO
			// Remove player
			_hash ^= _hashValues[cellData][positionTo];
			// Insert empty tile
			_hash ^= _hashValues[HasTile | IsEmpty][positionTo];
			break;
				   }

		case JUMP: {
			int cellData = GetCellData(move.GetFromCell());

			// FROM
			// Remvoe empty tile
			_hash ^= _hashValues[HasTile | IsEmpty][positionFrom];
			// Insert player
			_hash ^= _hashValues[cellData][positionFrom];

			// TO
			// Remove player
			_hash ^= _hashValues[cellData][positionTo];
			// Insert player
			_hash ^= _hashValues[HasTile | IsEmpty][positionTo];
			break;
				   }
		}
	}
	
	int ZobristHashing::GetDataForPlayer(const Vector2D& position) {
		if (_board->GetRelativeCellAt(position).IsMaxPiece()) {
			return IsMax;
		} else {
			return 0;
		}
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

		// Rebase the hash as we received a potentially different board
		_hash = RecaclulateHash();
	}

	long long ZobristHashing::RecaclulateHash() {
		long long hash = 0;
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

	long long ZobristHashing::GetHash() {
		return _hash;
	}

}
