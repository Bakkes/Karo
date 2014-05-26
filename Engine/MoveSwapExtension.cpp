#include "MoveSwapExtension.h"
#include <algorithm>
#include <Windows.h>
namespace engine{

	MoveSwapExtension::MoveSwapExtension(void)
	{
	}


	MoveSwapExtension::~MoveSwapExtension(void)
	{
	}

	void MoveSwapExtension::Start(const int& maxDepth){
		AIExtension::Start(maxDepth);
		_killerMoves = new EvalResult[maxDepth];
	}
	void MoveSwapExtension::End(){
		delete []_killerMoves;
	}
	void MoveSwapExtension::Step(const Players& player, const int& currentDepth, EvalResult&){
		_depth = currentDepth;
	}

	bool MoveSwapExtension::ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player) {
		if(!ShouldSwap()){
			return true;
		}
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
		if(!ShouldSwap()){
			return;
		}
		int findResult = find(moves.begin(),moves.end(),_killerMoves[depth].GetMove())-moves.begin();
		if(findResult > 0 && ((unsigned)findResult < moves.size())){
			moves[findResult]=moves[0];
			moves[0]=_killerMoves[depth].GetMove();
		}
	}
	bool MoveSwapExtension::ShouldSwap(){
		if(_depth == (GetMaxDepth() - 1)){
			return false;
		}
		return true;
	}
}