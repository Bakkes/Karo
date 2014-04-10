#pragma once
namespace Engine {

	enum MoveType { INSERT, MOVE, JUMP };
	enum MoveDirection { NORTH, EAST, SOUTH, WEST };
	
	class Move {
	public:
		Move(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile);
	private:
		MoveType _moveType;
		int _fromTile;
		int _toTile;
		MoveDirection _moveDirection;
		int _emptyTile;

		void init(MoveType moveType, int fromTile, int toTile, MoveDirection moveDirection, int emptyTile);
	};
}