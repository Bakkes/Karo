#include "AIExtension.h"
namespace engine{

	AIExtension::AIExtension(void)
	{}

	AIExtension::~AIExtension(void)
	{
	}

	void AIExtension::UpdateMoves(std::vector<Move>& moves){}
	const bool& AIExtension::ShouldContinue(const EvalResult& evalresult, const Players& player){
		return true;
	}
	void AIExtension::Step(EvalResult&){}

	void AIExtension::Start(){}
		// notify the exntension taht minmax ends
	void AIExtension::End(){}
}