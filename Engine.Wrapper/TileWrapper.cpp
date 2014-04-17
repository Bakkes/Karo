#include "TileWrapper.h"

namespace engine {
namespace wrapper {
	TileWrapper::TileWrapper(double x, double y, int data)
	{
		_tile = new Tile<int>(new Vector2D(x, y));
		_data = data;
	}

	TileWrapper::~TileWrapper(void)
	{
		delete _tile;
	}

	int TileWrapper::GetData() {
		return _data;
	}

	Vector2DWrapper^ TileWrapper::GetPosition() {
		return gcnew Vector2DWrapper(_tile->GetPosition()->X(), _tile->GetPosition()->Y());
	}
}
}