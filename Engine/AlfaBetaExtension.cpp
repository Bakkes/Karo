#include "AlfaBetaExtension.h"
namespace engine{

	AlfaBetaExtension::AlfaBetaExtension(void)
	{
	}


	AlfaBetaExtension::~AlfaBetaExtension(void)
	{
	}
	void AlfaBetaExtension::Step(const Players& player,const int& currentDepth, EvalResult& result){
		if (player == Max) {
			result.SetScore(INT_MIN);
		} else {
			result.SetScore(INT_MAX);
		}
	}
	bool AlfaBetaExtension::ShouldContinue(const EvalResult& score, EvalResult& result, const Players& player){
		if (player == Max) {
			if (score.GetScore() >= result.GetBestForMin() && result.GetBestForMin() != INT_MAX) {
				//cutoff
				return false;
			} else if (score.GetScore() > result.GetBestForMax()) {
				result.SetBestForMax(score.GetScore());
				result.SetMove(score.GetMove());
			}
		} else  if (player == Min)  {
			if (score.GetScore() <= result.GetBestForMax() && result.GetBestForMax() != INT_MIN) {
				// Cut off
				return false;
			} else if (score.GetScore() < result.GetBestForMin()) {
				result.SetBestForMin(score.GetScore());
				result.SetMove(score.GetMove());
			}
		}
		return true;
	}

}