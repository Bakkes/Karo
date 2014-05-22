#include "AIFactory.h"

namespace engine{
	AIFactory::AIFactory(IBoard* board, int maxDepth)
	{
		_board = board;
		_maxDepth = maxDepth;
	}


	AIFactory::~AIFactory(void)
	{
	// delete nothing, because not responsiblibty of factory to delete stuff
	}
	AI* AIFactory::CreateAI(){
		return new AI(_board, _maxDepth);
	}
	AI* AIFactory::CreateAlfaAI(){
		AI* result = CreateAI();
		result->AddExtension(new AlfaBetaExtension());
		return result;
	}
	AI* AIFactory::CreateMoveOrderingAlfaAI(){
		AI* result = CreateAlfaAI();
		result->AddExtension(new MoveSwapExtension());
		return result;
	}

	IBoard* AIFactory::GetBoard() const{
		return _board;
	}
}