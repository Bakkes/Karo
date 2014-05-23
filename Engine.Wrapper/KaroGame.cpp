#pragma once

#include "KaroGame.h"
#include "Board.h"
#include "WrapperConversionUtility.h"
#include "StaticEvaluation.h"
#include "ComputerPlayerUtils.h"
#include "Players.h"
#include "AIFactory.h"
namespace engine {
namespace wrapper {

	KaroGame::KaroGame() {
		_board = gcnew BoardWrapper();
		
	}

	KaroGame::~KaroGame() {
		this->!KaroGame();
	}

	KaroGame::!KaroGame() {
		delete _board;
		_board = nullptr;
	}

	BoardWrapper^ KaroGame::GetBoard() {
		return _board;
	}
	void KaroGame::ExecuteMove(MoveWrapper^ moveWrapper, engine::wrapper::Players player) {
		_board->ExecuteMove(moveWrapper, player);
	}

	MoveWrapper^ KaroGame::GetBestMove() {
		AI* _cPlayer = AIFactory(_board->GetInternalBoardCopy(), 3).CreateMoveOrderingAlfaAI();
		_cPlayer->SetEvaluator(new StaticEvaluation());
		Move bestMove = _cPlayer->GetBestMove(engine::wrapper::Max);
		MoveWrapper^ wrapped = WrapperConversionUtility().ConvertMove(bestMove);

		delete _cPlayer;
		return wrapped;
	}

	bool KaroGame::HasWon(engine::wrapper::Players player) {
		return ComputerPlayerUtils::IsWinningState(_board->GetInternalBoard(), static_cast<engine::Players>(player));
	}
}
}