#pragma once
#include "Tile.h"
#include "Vector2DWrapper.h"
namespace engine {
namespace wrapper {
public ref class TileWrapper
{
public:
	TileWrapper(double x, double y, int data);
	~TileWrapper(void);
	int GetData();
	Vector2DWrapper^ GetPosition();
private:
	Tile<int> * _tile;
	int _data;
};

}
}