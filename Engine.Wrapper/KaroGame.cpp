#pragma once

#include "stdafx.h"
#include "KaroGame.h"
#include "Board.h"
#include "WrapperConversionUtility.h"
namespace engine {
namespace wrapper {

	KaroGame::KaroGame() {
		_board = gcnew BoardWrapper();
		_cPlayer = new ComputerPlayer();
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
		Move bestMove = _cPlayer->GetBestMove();
		MoveWrapper^ wrapped = WrapperConversionUtility().ConvertMove(bestMove);

		return wrapped;
	}
}
}