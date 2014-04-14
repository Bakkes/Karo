#pragma once
#include "Move.h"
#include "IBoard.h"
#include <vector>
namespace engine {
	class ISafeBoard : IBoard {
	public:
		virtual IBoard* CopyToUnsafeBoard() = 0;
	};

}