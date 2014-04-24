#include "stdafx.h"
#include "CellWrapper.h"

namespace engine {
namespace wrapper {
	CellWrapper::CellWrapper(double x, double y, int data)
	{
		_tile = new Cell<int>(new Vector2D(x, y));
		_data = data;
	}

	CellWrapper::~CellWrapper(void)
	{
		delete _tile;
	}

	int CellWrapper::GetData() {
		return _data;
	}

	Vector2DWrapper^ CellWrapper::GetPosition() {
		return gcnew Vector2DWrapper(_tile->GetPosition()->X(), _tile->GetPosition()->Y());
	}
}
}