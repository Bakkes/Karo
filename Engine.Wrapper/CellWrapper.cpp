#include "CellWrapper.h"

namespace engine {
namespace wrapper {
	CellWrapper::CellWrapper(RelativeCell cell)
	{
		_cell = new RelativeCell(cell);
	}
	CellWrapper::~CellWrapper(void){
		delete _cell;
	}

	Vector2DWrapper^ CellWrapper::GetRelativePosition() {
		return gcnew Vector2DWrapper(_cell->GetRelativePosition().X(), _cell->GetRelativePosition().Y());
	}
	Vector2DWrapper^ CellWrapper::GetAbsolutePosition() {
		return gcnew Vector2DWrapper(_cell->GetAbsolutePosition().X(), _cell->GetAbsolutePosition().Y());
	}
	int CellWrapper::GetData() {
		return _cell->GetData();
	}
	int CellWrapper::HasTile() {
		return _cell->HasTile();
	}
	int CellWrapper::IsEmpty() {
		return _cell->IsEmpty();
	}
	int CellWrapper::IsMaxPiece() {
		return _cell->IsMaxPiece();
	}
	int CellWrapper::IsFlipped() {
		return _cell->IsFlipped();
	}
	RelativeCell CellWrapper::getCell() {
		return *_cell;
	}
}
}