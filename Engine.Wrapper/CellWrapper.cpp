#include "CellWrapper.h"

namespace engine {
namespace wrapper {
	CellWrapper::CellWrapper(RelativeCell cell)
	{
		_cell = new RelativeCell(cell);
	}

	CellWrapper::~CellWrapper(void){
		this->!CellWrapper();
	}

	CellWrapper::!CellWrapper(void){
		delete _cell;
		_cell = nullptr;
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
	bool CellWrapper::HasTile() {
		return _cell->HasTile() != 0;
	}
	bool CellWrapper::IsEmpty() {
		return _cell->IsEmpty() != 0;
	}
	bool CellWrapper::IsMaxPiece() {
		return _cell->IsMaxPiece() != 0;
	}
	bool CellWrapper::IsFlipped() {
		return _cell->IsFlipped() != 0;
	}
	RelativeCell CellWrapper::getCell() {
		return *_cell;
	}
}
}