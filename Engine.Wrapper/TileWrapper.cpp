#include "stdafx.h"
#include "TileWrapper.h"

namespace engine {
namespace wrapper {
	TileWrapper::TileWrapper(double x, double y)
	{
		_tile = new Tile<int>(new Vector2D(x, y));
	}

	TileWrapper::~TileWrapper(void)
	{
		delete _tile;
	}

	int TileWrapper::GetData() {
		return *(_tile->GetData());
	}

	Vector2DWrapper^ TileWrapper::GetPosition() {
		return gcnew Vector2DWrapper(_tile->GetPosition()->X(), _tile->GetPosition()->Y());
	}
}
}