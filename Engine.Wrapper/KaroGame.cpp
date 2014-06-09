#pragma once

#include "KaroGame.h"
#include "Board.h"
#include "WrapperConversionUtility.h"
#include "StaticEvaluation.h"
#include "ComputerPlayerUtils.h"
#include "Players.h"
#include "AIFactory.h"
#include "AltEval.h"
#include "RngTimeBased.h"

namespace engine {
namespace wrapper {

	KaroGame::KaroGame() {
		_board = gcnew BoardWrapper();
		_transpositionTable = new TranspositionTable(100000);
		
		IRng* rand = new RngTimeBased();
		_hasher = new ZobristHashing(nullptr, rand);
		delete rand;
		_prefferedAI = 5;
	}

	void KaroGame::SetAI(int to){
		_prefferedAI = to;
	}
	KaroGame::~KaroGame() {
		this->!KaroGame();
	}

	KaroGame::!KaroGame() {
		delete _board;
		delete _transpositionTable;
		delete _hasher;
		_board = nullptr;
	}

	BoardWrapper^ KaroGame::GetBoard() {
		return _board;
	}
	void KaroGame::ExecuteMove(MoveWrapper^ moveWrapper, engine::wrapper::Players player) {
		_board->ExecuteMove(moveWrapper, player);
	}

	void KaroGame::UndoMove(MoveWrapper^ moveWrapper, engine::wrapper::Players player) {
		_board->UndoMove(moveWrapper, player);
	}

	MoveWrapper^ KaroGame::GetBestMove() {
		IBoard* cpBoard = _board->GetInternalBoardCopy();
		AI* cPlayer = AIFactory(cpBoard, _hasher, _transpositionTable, 3).CreateAI(_prefferedAI);
		_hasher->UpdateBoard(cpBoard);
		cPlayer->SetEvaluator(new AltEval());
		Move bestMove = cPlayer->GetBestMove(engine::wrapper::Max);
		MoveWrapper^ wrapped = WrapperConversionUtility().ConvertMove(bestMove);

		_staticEvalCallCount = cPlayer->GetStaticEvalCallCount();
		_nodesSeen = cPlayer->GetNodesSeenCount();

		delete cPlayer;
		delete cpBoard;
		return wrapped;
	}

	bool KaroGame::HasWon(engine::wrapper::Players player) {
		return ComputerPlayerUtils::IsWinningState(_board->GetInternalBoard(), static_cast<engine::Players>(player));
	}

	int KaroGame::GetStaticEvalCallCount() {
		return _staticEvalCallCount;
	}

	int KaroGame::GetNodesSeenCount() {
		return _nodesSeen;
	}
}
}