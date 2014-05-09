#pragma once

#include "KaroGame.h"
#include "Board.h"
#include "WrapperConversionUtility.h"
#include "StaticEvaluation.h"
namespace engine {
namespace wrapper {

	KaroGame::KaroGame() {
		_board = gcnew BoardWrapper();
		
	}

	KaroGame::~KaroGame() {
		delete _board;
	}

	BoardWrapper^ KaroGame::GetBoard() {
		return _board;
	}

	void KaroGame::ExecuteMove(MoveWrapper^ moveWrapper, engine::wrapper::Players player) {
		_board->ExecuteMove(moveWrapper, player);
	}

	MoveWrapper^ KaroGame::GetBestMove() {
		ComputerPlayer _cPlayer = ComputerPlayer(_board->GetInternalBoard(), 5); // TODO GET COPY!
		_cPlayer.SetEvaluator(new StaticEvaluation());
		Move bestMove = _cPlayer.GetBestMove(Max);
		MoveWrapper^ wrapped = WrapperConversionUtility().ConvertMove(bestMove);
		return wrapped;
	}

	bool KaroGame::HasWon(engine::wrapper::Players player) {
		return false;
	}
}
}