#include "AIExtension.h"
namespace engine{

	AIExtension::AIExtension(void)
	{
		_board = nullptr;
	}

	AIExtension::~AIExtension(void)
	{
	}

	void AIExtension::UpdateMoves(const int& depth,std::vector<Move>& moves){}
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
	IStaticEvaluation& AIExtension::GetEvaluator() const{
		return *_evaluator;
	}
	int AIExtension::GetMaxDepth() const{
		return _maxDepth;
	}
	IBoard& AIExtension::GetBoard() const{
		return *_board;
	}
}