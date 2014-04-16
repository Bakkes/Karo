#pragma once
#include "Tile.h"

namespace engine {
namespace wrapper {
ref class TileWrapper
{
public:
	TileWrapper(double x, double y);
	~TileWrapper(void);
	int GetData();
	double GetX();
	double GetY();
private:
	Tile<int> * _tile;
};

}
}