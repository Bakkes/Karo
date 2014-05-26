#include "MiniMaxExtension.h"
namespace engine{

	MiniMaxExtension::MiniMaxExtension(void)
	{
	}


	MiniMaxExtension::~MiniMaxExtension(void)
	{
	}

	void MiniMaxExtension::Step(const Players& player,const int& currentDepth, EvalResult& result){
		if (player == Max) {
			result.SetScore(INT_MIN);
		} else {
			result.SetScore(INT_MAX);
		}
	}

	bool MiniMaxExtension::ShouldContinue(const EvalResult& score, EvalResult& result, const Players& player){
		if (
			(player == Max && score.GetScore() > result.GetScore()) ||
			(player == Min && score.GetScore() < result.GetScore()))
		{
			result.SetScore(score.GetScore());
			result.SetMove(score.GetMove());
		}
		return true;
	}

}