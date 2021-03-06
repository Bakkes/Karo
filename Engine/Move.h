#pragma once
#include "Vector2D.h"

namespace engine {

	enum MoveType { INSERT, STEP, JUMP };
	
	/** NOTE: Move positions use the absolute coordinates */
	class ENGINE_API Move {
	public:
		Move(const Move&);
		// Creates either a INSERT or DELETE move
		Move(MoveType type, Vector2D toCell);
		// Creates either a MOVE or JUMP move which does NOT change the board structure
		Move(MoveType type, Vector2D fromCell, Vector2D toCell);
		// Creates either a MOVE or JUMP move which DOES change the board structure
		Move(MoveType type, Vector2D fromCell, Vector2D toCell, Vector2D usedCell);
		// The type of the move
		const MoveType& GetMoveType() const;
		// The location from which the piece will come from
		const Vector2D& GetFromCell() const;
		// The location to which the piece will go to
		const Vector2D& GetToCell() const;
		// The location of the tile used to jump to (OPTIONAL: Test with HasUsedCell to see if it is set!)
		const Vector2D& GetUsedCell() const;
		// If a tile was moved to make this move possible
		const bool& HasUsedCell() const;

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

	inline bool operator==(const Move& lhs, const Move& rhs) {
		if (lhs.GetMoveType() != rhs.GetMoveType())
			return false;

		if (lhs.GetFromCell() != rhs.GetFromCell())
			return false;

		if (lhs.GetToCell() != rhs.GetToCell())
			return false;

		if (lhs.HasUsedCell() != rhs.HasUsedCell())
			return false;

		if (lhs.HasUsedCell() && lhs.GetUsedCell() != rhs.GetUsedCell())
			return false;

		return true;
	}

	inline bool operator!=(const Move& lhs, const Move& rhs) { return !(lhs == rhs);}

}
