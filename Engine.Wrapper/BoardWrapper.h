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
public ref class BoardWrapper
{
public:
	BoardWrapper(void);
	~BoardWrapper(void);
	void ExecuteMove(MoveWrapper^ mw, engine::wrapper::Players player);
	List<TileWrapper^>^ GetOccupiedTiles();
	TileWrapper^ GetRelativeTileAt(Vector2DWrapper^ relativePosition);
private:
	Board * _board;
};

}
}