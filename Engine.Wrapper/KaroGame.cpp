#pragma once

#include "stdafx.h"
#include "KaroGame.h"
#include "Board.h"
namespace engine {
namespace wrapper {

	KaroGame::KaroGame() {
		board = new Board();
	}

	KaroGame::~KaroGame() {

	}
}
}