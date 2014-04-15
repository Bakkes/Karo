#pragma once

#include "DllImportExport.h"

namespace engine {

	enum MoveType { INSERT, MOVE, JUMP, DELETE};
	enum MoveDirection { NORTH, EAST, SOUTH, WEST, NONE };
	
	class Move {
	public:
		ENGINE_API Move(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile);
		MoveType ENGINE_API GetMoveType();
		int ENGINE_API GetFromTile();
		int ENGINE_API GetToTile();
		MoveDirection ENGINE_API GetMoveDirection();
		int ENGINE_API GetEmptyTile();

	private:
		MoveType _moveType;
		int _fromTile;
		int _toTile;
		MoveDirection _moveDirection;
		int _emptyTile;

		void init(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile);
	};
}