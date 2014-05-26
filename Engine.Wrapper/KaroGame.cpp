#pragma once

#include "KaroGame.h"
#include "Board.h"
#include "WrapperConversionUtility.h"
#include "StaticEvaluation.h"
#include "ComputerPlayerUtils.h"
#include "Players.h"
#include "AIFactory.h"
#include "AltEval.h"

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
		IBoard* cpBoard = _board->GetInternalBoardCopy();
		AI* cPlayer = AIFactory(cpBoard, 3).CreateMoveOrderingAlfaAI();
		cPlayer->SetEvaluator(new AltEval());
		Move bestMove = cPlayer->GetBestMove(engine::wrapper::Max);
		MoveWrapper^ wrapped = WrapperConversionUtility().ConvertMove(bestMove);

		delete cPlayer;
		delete cpBoard;
		return wrapped;
	}

	bool KaroGame::HasWon(engine::wrapper::Players player) {
		return ComputerPlayerUtils::IsWinningState(_board->GetInternalBoard(), static_cast<engine::Players>(player));
	}
}
}