#pragma once
#include "Vector2D.h"

namespace engine {

	enum MoveType { INSERT, MOVE, JUMP, DELETE };
	
	class ENGINE_API Move {
	public:
		// Creates either a INSERT or DELETE move
		Move(MoveType type, Vector2D toTile);
		// Creates either a MOVE or JUMP move which does NOT change the board structure
		Move(MoveType type, Vector2D fromTile, Vector2D toTile);
		// Creates either a MOVE or JUMP move which DOES change the board structure
		Move(MoveType type, Vector2D fromTile, Vector2D toTile, Vector2D usedTile);
		// The type of the move
		MoveType GetMoveType();
		// The location from which the piece will come from
		Vector2D GetFromTile();
		// The location to which the piece will go to
		Vector2D GetToTile();
		// The location of the tile used to jump to (OPTIONAL: Test with HasUsedTile to see if it is set!)
		Vector2D GetUsedTile();
		// If a tile was moved to make this move possible
		bool HasUsedTile();

	private:
		// The type of the move
		MoveType _moveType;
		// The location from which the piece will come from
		Vector2D _fromTile;
		// The location to which the piece will go to
		Vector2D _toTile;
		// The location of the tile used to jump to (OPTIONAL: Test with HasUsedTile to see if it is set!)
		Vector2D _usedTile;
		// If a tile was moved to make this move possible
		bool _hasUsedTile;

		void Init(MoveType moveType, Vector2D fromTile, Vector2D toTile, Vector2D tile, bool hasUsedTile);
	};
}
