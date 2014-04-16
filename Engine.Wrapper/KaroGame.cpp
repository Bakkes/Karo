#pragma once

#include "stdafx.h"
#include "KaroGame.h"
#include "Board.h"
namespace engine {
namespace wrapper {

	KaroGame::KaroGame() {
		_board = new Board();
		_cPlayer = new ComputerPlayer(_board, 5);
	}

	KaroGame::~KaroGame() {
		delete _board;
		delete _cPlayer;
	}

	void KaroGame::ExecuteMove(MoveWrapper^ moveWrapper, engine::wrapper::Players player) {
		//Where do we clean this up
		Move * m = new engine::Move(static_cast<engine::MoveType>(moveWrapper->GetMoveType()), 
			moveWrapper->GetFromTile(), moveWrapper->GetToTile(), 
			static_cast<engine::MoveDirection>(moveWrapper->GetMoveDirection()), moveWrapper->GetEmptyTile());

		_board->ExecuteMove(m, static_cast<engine::Players>(player));
	}

	MoveWrapper^ KaroGame::GetBestMove() {
		Move bestMove = _cPlayer->GetBestMove(static_cast<engine::Players>(Players::Max));
		MoveWrapper^ wrapped = gcnew MoveWrapper(static_cast<engine::wrapper::MoveType>(bestMove.GetMoveType()), 
			bestMove.GetFromTile(), bestMove.GetToTile(), static_cast<engine::wrapper::MoveDirection>(bestMove.GetMoveDirection()), 
			bestMove.GetEmptyTile());

		return wrapped;
	}
}
}