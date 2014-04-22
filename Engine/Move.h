#pragma once
#include "Vector2D.h"

namespace engine {

	enum MoveType { INSERT, MOVE, JUMP, DELETE };
	
	/** NOTE: Move positions use the absolute coordinates */
	class ENGINE_API Move {
	public:
		// Creates either a INSERT or DELETE move
		Move(MoveType type, Vector2D toCell);
		// Creates either a MOVE or JUMP move which does NOT change the board structure
		Move(MoveType type, Vector2D fromCell, Vector2D toCell);
		// Creates either a MOVE or JUMP move which DOES change the board structure
		Move(MoveType type, Vector2D fromCell, Vector2D toCell, Vector2D usedCell);
		// The type of the move
		MoveType GetMoveType();
		// The location from which the piece will come from
		Vector2D GetFromCell();
		// The location to which the piece will go to
		Vector2D GetToTile();
		void SetToTile(Vector2D location);
		// The location of the tile used to jump to (OPTIONAL: Test with HasUsedTile to see if it is set!)
		Vector2D GetUsedTile();
		// If a tile was moved to make this move possible
		bool HasUsedCell();

	private:
		// The type of the move
		MoveType _moveType;
		// The location from which the piece will come from
		Vector2D _fromCell;
		// The location to which the piece will go to
		Vector2D _toCell;
		// The location of the tile used to go to an empty (OPTIONAL: Test with HasUsedCell to see if it is set!)
		Vector2D _usedCell;
		// If a tile was moved to make this move possible
		bool _hasUsedCell;

		void Init(MoveType moveType, Vector2D fromCell, Vector2D toCell, Vector2D tile, bool hasUsedCell);
	};
}
