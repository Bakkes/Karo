#pragma once

#include "stdafx.h"
#include "KaroGame.h"
#include "Board.h"
#include "WrapperConversionUtility.h"
namespace engine {
namespace wrapper {

	KaroGame::KaroGame() {
		_board = new Board();
		_cPlayer = new ComputerPlayer();
	}

	KaroGame::~KaroGame() {
		delete _board;
		delete _cPlayer;
	}

	void KaroGame::ExecuteMove(MoveWrapper^ moveWrapper, engine::wrapper::Players player) {
		//Where do we clean this up
		Move * m = WrapperConversionUtility().ConvertMove(moveWrapper);
		_board->ExecuteMove(m, static_cast<engine::Players>(player));
	}

	MoveWrapper^ KaroGame::GetBestMove() {
		Move bestMove = _cPlayer->GetBestMove();
		MoveWrapper^ wrapped = WrapperConversionUtility().ConvertMove(bestMove);

		return wrapped;
	}
}
}