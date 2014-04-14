#pragma once
namespace engine {
	class IUnsafeBoard {
		virtual void ExecuteMove(Move* move) = 0;
		virtual std::vector<Move>* GetLegalMoves() = 0;
	};
}