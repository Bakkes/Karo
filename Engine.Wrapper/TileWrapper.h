#pragma once
#include "Tile.h"
#include "Vector2DWrapper.h"
namespace engine {
namespace wrapper {
ref class TileWrapper
{
public:
	TileWrapper(double x, double y);
	~TileWrapper(void);
	int GetData();
	Vector2DWrapper^ GetPosition();
private:
	Tile<int> * _tile;
};

}
}