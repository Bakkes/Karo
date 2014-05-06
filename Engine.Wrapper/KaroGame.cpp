#pragma once

#include "KaroGame.h"
#include "Board.h"
#include "WrapperConversionUtility.h"
#include "StaticEvaluation.h"
namespace engine {
namespace wrapper {

	KaroGame::KaroGame() {
		_board = gcnew BoardWrapper();
		_cPlayer = new ComputerPlayer(_board->GetInternalBoard(), 5);
		_cPlayer->SetEvaluator(new StaticEvaluation());
	}

	KaroGame::~KaroGame() {
		delete _board;
		delete _cPlayer;
	}

	BoardWrapper^ KaroGame::GetBoard() {
		return _board;
	}

	void KaroGame::ExecuteMove(MoveWrapper^ moveWrapper, engine::wrapper::Players player) {
		_board->ExecuteMove(moveWrapper, player);
	}

	MoveWrapper^ KaroGame::GetBestMove() {
		Move bestMove = _cPlayer->GetBestMove(Max);
		MoveWrapper^ wrapped = WrapperConversionUtility().ConvertMove(bestMove);
		return wrapped;
	}

	bool KaroGame::HasWon(engine::wrapper::Players player) {
		return false;
	}
}
}