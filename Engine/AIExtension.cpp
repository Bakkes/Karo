#include "AIExtension.h"
namespace engine{

	AIExtension::AIExtension(void)
	{}

	AIExtension::~AIExtension(void)
	{
	}

	void AIExtension::UpdateMoves(const int& depth,std::vector<Move>& moves){}

	void AIExtension::OnExecutedMove(const Move& move) {}

	void AIExtension::OnUndoMove(const Move& move) {}

	bool AIExtension::ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player){
		return true;
	}
	void AIExtension::Step(const Players& player,const int& currentDepth, EvalResult&){}

	void AIExtension::Start(const int& maxDepth){
		_maxDepth = maxDepth;
	}
		// notify the exntension taht minmax ends
	void AIExtension::End(){}
	int AIExtension::GetMaxDepth() const{
		return _maxDepth;
	}
}