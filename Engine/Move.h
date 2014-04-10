#pragma once
namespace Engine {

	enum MoveType { INSERT, MOVE, JUMP };
	enum MoveDirection { NORTH, EAST, SOUTH, WEST };
	
	class Move
	{
	public:
		Move(MoveType, int, int, MoveDirection, int);
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

		void init(MoveType, int, int, MoveDirection, int);
	};
}