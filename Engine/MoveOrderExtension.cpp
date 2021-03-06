#include "MoveOrderExtension.h"


namespace engine{
	MoveOrderExtension::MoveOrderExtension(void)
	{
	}

	MoveOrderExtension::~MoveOrderExtension(void)
	{
	}
	void MoveOrderExtension::Step(const Players& player,const int& currentDepth, EvalResult&){
		_shouldOrder = currentDepth == 0;
		_player = player;
	}
	void MoveOrderExtension::UpdateMoves(std::vector<Move>& moves){
		if(!_shouldOrder){
			return;
		}

		int y = 0;
		sort(moves.begin(), moves.end(), [this](const Move& one, const Move& two) -> bool{
			if(one == two){
				return false;
			}
			GetBoard()->ExecuteMove(one, _player);
			int lhs = GetEvaluator()->Eval(GetBoard(), _player);
			GetBoard()->UndoMove(one, _player);
			GetBoard()->ExecuteMove(two, _player);
			int rhs = GetEvaluator()->Eval(GetBoard(), _player);
			GetBoard()->UndoMove(two, _player);
			// invert the result for descending value
			return rhs < lhs; 
		});
	}
}