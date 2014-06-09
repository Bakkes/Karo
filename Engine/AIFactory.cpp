#include "AIFactory.h"

namespace engine{
	AIFactory::AIFactory(IBoard* board, ZobristHashing* hasher, TranspositionTable* table, int maxDepth)
	{
		_board = board;
		_maxDepth = maxDepth;
		ZobristHashing* _hasher = hasher;
		TranspositionTable* _table = table;
	}

	AIFactory::~AIFactory(void)
	{
	// delete nothing, because not responsiblibty of factory to delete stuff
	}

	AI* AIFactory::CreateAI(unsigned which){
		switch(which){
			case 0:
				return CreateAI();
			case 1:
				return CreateAlfaAI();
			case 2:
				return CreateMoveOrderingAlfaAI();
		}
		// fancyesd ai in all other cases
		// because unsigned it will be more fancy
		return CreateMoveOrderingAlfaZorbristAI();
	}
	AI* AIFactory::CreateAI(){
		AI* result = new AI(_board, _maxDepth);
		result->AddExtension(new MiniMaxExtension());
		return result;
	}

	AI* AIFactory::CreateAlfaAI(){
		AI* result = new AI(_board, _maxDepth); 
		result->AddExtension(new AlfaBetaExtension());
		return result;
	}

	AI* AIFactory::CreateMoveOrderingAlfaAI(){
		AI* result = CreateAlfaAI();
		result->AddExtension(new MoveOrderExtension());
		result->AddExtension(new MoveSwapExtension());
		return result;
	}

	AI* AIFactory::CreateMoveOrderingAlfaZorbristAI() {
		AI* result = CreateMoveOrderingAlfaAI();
		result->AddExtension(new TranspositionExtension(_hasher, _table));
		return result;
	}

	IBoard* AIFactory::GetBoard() const{
		return _board;
	}
}