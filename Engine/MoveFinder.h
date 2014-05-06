#pragma once

#include "DllImportExport.h"
#include "Board.h"
#include "Players.h"
#include "Move.h"

namespace engine{
	class Board;

	class ENGINE_API MoveFinder
	{
	public:
		MoveFinder(Board* board);
		~MoveFinder(void);
		std::vector<Move>* GetLegalMoves(Players player);
	private:
		// Get all legal moves for the place state.
		std::vector<Move>* GetLegalPlaceMoves(Players player);

		// Get all legal moves for the move state.
		std::vector<Move>* GetLegalMoveMoves(Players player);
		void AddAdjacentMovesToVector(std::vector<Move>* moves, Cell<int> source);
		void AddJumpMovesToVector(std::vector<Move>* moves, Cell<int> source);
		void AddTileMoveMoves(std::vector<Move>* moves, MoveType type, Cell<int> from, Cell<int> to);
		void AddMoveIfValidDestination(
			std::vector<Move>* moves,
			const Cell<int> &from,
			const Cell<int> &to,
			MoveType type);
		Board* _board;
	};
}