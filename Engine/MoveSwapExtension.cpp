#include "MoveSwapExtension.h"
#include <algorithm>
namespace engine{

	MoveSwapExtension::MoveSwapExtension(void)
	{
	}


	MoveSwapExtension::~MoveSwapExtension(void)
	{
	}

	void MoveSwapExtension::Start(const int& maxDepth){
		_killerMoves = new EvalResult[maxDepth];
	}
	void MoveSwapExtension::End(){
		delete []_killerMoves;
	}
	void MoveSwapExtension::Step(const Players& player, const int& currentDepth, EvalResult&){
		_depth = currentDepth;
	}

	bool MoveSwapExtension::ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player) {
		if (player == Max) {
			if(currentResult.GetBestForMax()>_killerMoves[_depth].GetBestForMax()){
				_killerMoves[_depth]=currentResult;
			}
		}else{
			if(currentResult.GetBestForMin()<_killerMoves[_depth].GetBestForMin()){
				_killerMoves[_depth]=currentResult;
			}
		}
		return true;
	}
	void MoveSwapExtension::UpdateMoves(const int& depth, std::vector<Move>& moves){
		int findResult = find(moves.begin(),moves.end(),_killerMoves[depth].GetMove())-moves.begin();
		if(findResult > 0 && ((unsigned)findResult < moves.size())){
			moves[findResult]=moves[0];
			moves[0]=_killerMoves[depth].GetMove();
		}
	}
}