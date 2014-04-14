#pragma once
namespace engine {

	enum MoveType { INSERT = 0, MOVE = 1, JUMP = 2};
	enum MoveDirection { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };
	
	class Move {
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