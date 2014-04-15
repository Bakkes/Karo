#pragma once

#include "MoveWrapper.h"
#include "Board.h"
#include "ComputerPlayer.h"
#include "PlayersWrapper.h"
using namespace engine;

namespace engine {
namespace wrapper {
	public ref class KaroGame
	{
		public:
			KaroGame();
			~KaroGame();
			MoveWrapper^ GetBestMove();
			void ExecuteMove(MoveWrapper^ w, engine::wrapper::Players player);
		private:
			Board * _board;
			ComputerPlayer * _cPlayer;
	};
}
}