#include "AIExtension.h"
namespace engine{

	AIExtension::AIExtension(void)
	{
		_board = nullptr;
	}

	AIExtension::~AIExtension(void)
	{
	}

	void AIExtension::UpdateMoves(std::vector<Move>& moves){}
	
	void AIExtension::UpdateMoves(std::vector<Move>& moves, Players player, int depth){
		// Overload call for the old API
		this->UpdateMoves(moves);
	}

	void AIExtension::OnExecuteMove(const Move& move) {}

	void AIExtension::OnUndoMove(const Move& move) {}

	bool AIExtension::ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player){
		return true;
	}
	void AIExtension::Step(const Players& player,const int& currentDepth, EvalResult&){
		_currentDepth = currentDepth;
	}

	void AIExtension::Start(const int& maxDepth, IBoard* board, IStaticEvaluation* evaluation){
		_maxDepth = maxDepth;
		_board = board;
		_evaluator = evaluation;
	}
		// notify the exntension taht minmax ends
	void AIExtension::End(){}

	void AIExtension::RegisterBoard(EvalResult& result, int depth, Players player) {
	}

	IStaticEvaluation* AIExtension::GetEvaluator() const{
		return _evaluator;
	}
	int AIExtension::GetMaxDepth() const{
		return _maxDepth;
	}
	IBoard* AIExtension::GetBoard() const{
		return _board;
	}
	int AIExtension::GetCurrentDepth() const{
		return _currentDepth;
	}
}
