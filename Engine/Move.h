#pragma once
#include "DllImportExport.h"

namespace engine {

	enum ENGINE_API MoveType { INSERT = 0, MOVE = 1, JUMP = 2};
	enum ENGINE_API MoveDirection { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3, NONE = 4 };
	
	class ENGINE_API  Move {
	public:
		Move(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile);
		MoveType GetMoveType();
		int GetFromTile();
		int GetToTile();
		MoveDirection GetMoveDirection();
		int GetEmptyTile();

	private:
		MoveType _moveType;
		int _fromTile;
		int _toTile;
		MoveDirection _moveDirection;
		int _emptyTile;

		void init(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile);
	};
}
