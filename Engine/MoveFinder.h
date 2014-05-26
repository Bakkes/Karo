#pragma once

#include "DllImportExport.h"
#include "Players.h"
#include "Move.h"
#include "Board.h"
#include <vector>

namespace engine{
	class Board;
	class ENGINE_API MoveFinder
	{
	public:
		MoveFinder(Board* board);
		~MoveFinder(void);
		std::vector<Move> GetLegalMoves(Players player);

		// Invalidates the board, causing GetLegalMoves to generate new legal moves
		// the next time it is called.
		void Invalidate();
	private:
		Board* _board;

		// All the moves that movefinder has calculated so far.
		std::vector<Move>* _cachedMoves;

		// If the movefinder is invalidated, GetLegalMoves will generate new
		// legal moves. If not, it will return _cachedMoves.
		bool _invalidatedMax;
		bool _invalidatedMin;

		// Used for IsConnected method.
		std::vector<const RelativeCell>* _checkedCells;

		// Get all legal moves for the place state.
		std::vector<Move>* GetLegalPlaceMoves(Players player);

		// Get all legal moves for the move state.
		std::vector<Move>* GetLegalMoveMoves(Players player);
		void AddAdjacentMovesToVector(const RelativeCell& source);
		void AddJumpMovesToVector(const RelativeCell& source);
		void AddTileMoveMoves(
			const MoveType& type,
			const RelativeCell& from,
			const RelativeCell& to
		);
		void AddMoveIfValidDestination(
			const RelativeCell &from,
			const RelativeCell &to,
			const MoveType& type
		);
		int ConnectedTiles(const RelativeCell &start);
		int ConnectedTilesRecursive(const RelativeCell &start);

		bool CellHasTileWithPlayer(const RelativeCell &cell);
	};
}