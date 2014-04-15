#pragma once

#include "stdafx.h"
#include "KaroGame.h"
#include "Board.h"
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

	void KaroGame::ExecuteMove(MoveWrapper moveWrapper, engine::wrapper::Players player) {
		//Where do we clean this up
		Move * m = new engine::Move(static_cast<engine::MoveType>(moveWrapper.GetMoveType()), moveWrapper.GetFromTile(), moveWrapper.GetToTile(), static_cast<engine::MoveDirection>(moveWrapper.GetMoveDirection()), moveWrapper.GetEmptyTile());
		_board->ExecuteMove(m, static_cast<engine::Players>(player));
	}

	MoveWrapper ^ KaroGame::GetBestMove() {
		Move bestMove = _cPlayer->GetBestMove();
		MoveWrapper ^ wrapped = gcnew MoveWrapper(bestMove);
		return wrapped;
	}
}
}