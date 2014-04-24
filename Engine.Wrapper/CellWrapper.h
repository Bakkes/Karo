#pragma once
#include "Cell.h"
#include "Vector2DWrapper.h"
namespace engine {
namespace wrapper {
public ref class CellWrapper
{
public:
	CellWrapper(double x, double y, int data);
	~CellWrapper(void);
	int GetData();
	Vector2DWrapper^ GetPosition();
private:
	Cell<int> * _tile;
	int _data;
};

}
}