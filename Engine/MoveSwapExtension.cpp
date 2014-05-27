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

	void MoveSwapExtension::Start(const int& maxDepth, IBoard* board, IStaticEvaluation* eval){
		AIExtension::Start(maxDepth, board, eval);
		_killerMoves = new EvalResult[maxDepth];
	}
	void MoveSwapExtension::End(){
		delete []_killerMoves;
	}

	bool MoveSwapExtension::ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player) {
		if(!ShouldSwap()){
			return true;
		}
		if (player == Max) {
			if(currentResult.GetBestForMax()>_killerMoves[GetCurrentDepth()].GetBestForMax()){
				_killerMoves[GetCurrentDepth()]=currentResult;
			}
		}else{
			if(currentResult.GetBestForMin()<_killerMoves[GetCurrentDepth()].GetBestForMin()){
				_killerMoves[GetCurrentDepth()]=currentResult;
			}
		}
		return true;
	}
	void MoveSwapExtension::UpdateMoves(std::vector<Move>& moves){
		if(!ShouldSwap()){
			return;
		}
		int findResult = find(moves.begin(),moves.end(),_killerMoves[GetCurrentDepth()].GetMove())-moves.begin();
		if(findResult > 0 && ((unsigned)findResult < moves.size())){
			moves[findResult]=moves[0];
			moves[0]=_killerMoves[GetCurrentDepth()].GetMove();
		}
	}
	bool MoveSwapExtension::ShouldSwap(){
		if(GetCurrentDepth() == 0){
			return false;
		}
		if(GetCurrentDepth() == (GetMaxDepth() - 1)){
			return false;
		}
		return true;
	}
}