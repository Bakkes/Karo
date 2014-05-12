#pragma once

#include "DllImportExport.h"
#include "IBoard.h"
#include "Players.h"
#include "Move.h"
#include <vector>

namespace engine{
	class ENGINE_API MoveFinder
	{
	public:
		MoveFinder(IBoard* board);
		~MoveFinder(void);
		std::vector<Move>* GetLegalMoves(Players player);
	private:
		IBoard* _board;

		// Used for IsConnected method.
		std::vector<const RelativeCell>* _checkedCells;

		// Get all legal moves for the place state.
		std::vector<Move>* GetLegalPlaceMoves(Players player);

		// Get all legal moves for the move state.
		std::vector<Move>* GetLegalMoveMoves(Players player);
		void AddAdjacentMovesToVector(std::vector<Move>& moves, const RelativeCell& source);
		void AddJumpMovesToVector(std::vector<Move>& moves, const RelativeCell& source);
		void AddTileMoveMoves(
			std::vector<Move>& moves, 
			const MoveType& type, 
			const RelativeCell& from, 
			const RelativeCell& to
		);
		void AddMoveIfValidDestination(
			std::vector<Move>& moves,
			const RelativeCell &from,
			const RelativeCell &to,
			const MoveType& type
		);
		bool IsConnected(const RelativeCell &from, const RelativeCell &to);
		bool IsConnectedRecursive(const RelativeCell &from, const RelativeCell &to);
	};
}