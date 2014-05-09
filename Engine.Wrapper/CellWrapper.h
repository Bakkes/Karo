#pragma once
#include "RelativeCell.h"
#include "Vector2DWrapper.h"
namespace engine {
namespace wrapper {
using namespace engine;
public ref class CellWrapper
{
public:
	CellWrapper(RelativeCell);
	~CellWrapper(void);
	int GetData();
	Vector2DWrapper^ GetRelativePosition();
	Vector2DWrapper^ GetAbsolutePosition();
	int HasTile();
	int IsEmpty();
	int IsMaxPiece();
	int IsFlipped();
	RelativeCell getCell();
private:
	RelativeCell* _cell;
};

}
}