#pragma once

#include "Move.h"
#include "Players.h"

namespace engine {
	class ENGINE_API ComputerPlayerUtils
	{
	public:
		static Players InvertPlayer(Players player); 
	};
}
