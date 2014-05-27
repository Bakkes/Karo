#pragma once
#include "Players.h"
#include "EvalResult.h"
#include "Board.h"
#include <vector>
#include "IStaticEvaluation.h"
namespace engine {
	class AIExtension
	{
	public:
		AIExtension(void);
		virtual ~AIExtension(void);
		// notify the extension that the minmax starts, and give some crap to em
		virtual void Start(const int& maxDepth, IBoard* board, IStaticEvaluation* evaluation);
		// notify the exntension taht minmax ends
		virtual void End();

		// go one ply deeper, allows extension to do plystep initilization
		virtual void Step(const Players& player, const int& currentDepth, EvalResult&);

		// Notifies the Extension of which move will be executed
		// Called BEFORE the board state changes
		virtual void OnExecuteMove(const Move&);
		// Notifies the extension of which move will be undo
		// Called BEFORE the board state changes
		virtual void OnUndoMove(const Move&);
		// allows extension to do move ordering
		virtual void UpdateMoves(std::vector<Move>& moves);
		// allows extension to do pruning
		virtual bool ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player);

	protected:
		int GetMaxDepth() const;
		int GetCurrentDepth() const;
		IBoard* GetBoard() const;
		IStaticEvaluation* GetEvaluator() const;
	private:
		int _maxDepth;
		int _currentDepth;
		IBoard* _board;
		IStaticEvaluation* _evaluator;
	};


}