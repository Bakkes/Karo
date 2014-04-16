#pragma once

#include "Board.h"
#include "MoveWrapper.h"
#include "PlayersWrapper.h"
#include "TileWrapper.h"
#include "WrapperConversionUtility.h"
#include <vector>

using namespace System;
using namespace System::Collections::Generic;

namespace engine {
namespace wrapper {
ref class BoardWrapper
{
public:
	BoardWrapper(void);
	~BoardWrapper(void);
	void ExecuteMove(MoveWrapper^ mw, engine::wrapper::Players player);
	List<TileWrapper^>^ GetOccupiedTiles();
	TileWrapper^ GetRelativeTileAt(Vector2DWrapper^ relativePosition);
	// Gets the C++ Board (unwrapped)
	Board* GetInternalBoard();
private:
	Board * _board;
};

}
}