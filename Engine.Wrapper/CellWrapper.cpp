#include "CellWrapper.h"

namespace engine {
namespace wrapper {
	CellWrapper::CellWrapper(RelativeCell cell) : _cell(cell)
	{
	}

	int& CellWrapper::GetData() {

		_cell.GetData();
	}
	Vector2DWrapper^ CellWrapper::GetRelativePosition() {
		return gcnew Vector2DWrapper(this->_cell.GetRelativePosition().X(), this->_cell.GetRelativePosition().Y());
	}
	Vector2DWrapper^ CellWrapper::GetAbsolutePosition() {
		return gcnew Vector2DWrapper(this->_cell.GetAbsolutePosition().X(), this->_cell.GetAbsolutePosition().Y());
	}
	int& CellWrapper::HasTile() {
		return _cell.HasTile();
	}
	int& CellWrapper::IsEmpty() {
		return _cell.IsEmpty();
	}
	int& CellWrapper::IsMaxPiece() {
		return _cell.IsMaxPiece();
	}
	int& CellWrapper::IsFlipped() {
		return _cell.IsFlipped();
	}
	RelativeCell CellWrapper::getCell() {
		return _cell;
	}
}
}