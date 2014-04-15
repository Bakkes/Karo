#pragma once
#include <stack>

#include "IComputerPlayer.h"
#include "IStaticEvaluation.h"
#include "Players.h"

namespace engine {

	class ComputerPlayer : public IComputerPlayer {
	public:
		ComputerPlayer(IBoard* board, int maxDepth);
		~ComputerPlayer() override;
		virtual Move GetBestMove(Players player) override;

	private:
		// The Static Evaluation function which will evaluate the board
		IStaticEvaluation* _evaluator;
		// The maximum depth of the minimax search
		int _maxDepth;
		// The stack of the moves the AI has executed.
		std::stack<Move*> _moveHistory;
		// The unsafe board which is the playground of the AI
		IBoard* _board;
		// Executes a single step from the Minimax algorithm
		Move ENGINE_API MinimaxStep(Players player, int depth);
	};

	// Creates a move which is the exact opposite of the given move
	Move ENGINE_API InvertMove(Move move);
	// Creates the player which is the exact opposite of the given player
	Players ENGINE_API InvertPlayer();
	// Creates a move direction which is the exact opposite of the give move direction
	MoveDirection ENGINE_API InvertDirection(MoveDirection direction);
}
