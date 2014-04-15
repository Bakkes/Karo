#pragma once
namespace engine {

	enum MoveType { INSERT, MOVE, JUMP };
	enum MoveDirection { UP, LEFTUP, LEFT, LEFTDOWN, DOWN, RIGHTDOWN, RIGHT, RIGHTUP};
	
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