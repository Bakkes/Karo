#pragma once
#include "Move.h"
#include "IUnsafeBoard.h"
#include <vector>
namespace engine {
	class IBoard : IUnsafeBoard {
	public:
		virtual IUnsafeBoard CopyToUnsafeBoard() = 0;
	};

}