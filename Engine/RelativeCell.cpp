#include "RelativeCell.h"
#include "RelativeAbsoluteConverter.h"
namespace engine{
	RelativeCell::RelativeCell(Cell<int>* cell, RelativeAbsoluteConverter* converter) {
		Init(cell, converter);
	}

	RelativeCell::RelativeCell(const RelativeCell& cpy){
		Init(cpy._cell, cpy._converter);
	}

	void RelativeCell::Init(Cell<int>* cell, RelativeAbsoluteConverter* converter){
		_cell = cell;
		_converter = converter;
	}
	RelativeCell::~RelativeCell(){
		// dont delete anything, because this did not create anything!
	}
	const RelativeCell RelativeCell::GetBottom() const{
		return RelativeCell(_cell->GetBottom(), _converter);
	}
	const RelativeCell RelativeCell::GetRight() const{
		return RelativeCell(_cell->GetRight(), _converter);
	}
	const RelativeCell RelativeCell::GetLeft() const{
		return RelativeCell(_cell->GetLeft(), _converter);
	}
	const RelativeCell RelativeCell::GetTop() const{
		return RelativeCell(_cell->GetTop(), _converter);
	}

	Vector2D RelativeCell::GetRelativePosition() const {
		return _converter->ToRelative(_cell->GetPosition());
	}
	const Vector2D& RelativeCell::GetAbsolutePosition() const {
		return _cell->GetPosition();
	}

	int RelativeCell::GetData() const {
		return _cell->GetData();
	}
	int RelativeCell::HasTile() const{
		return GetData() & CellValue::HasTile;
	}
	int RelativeCell::IsEmpty() const{
		return GetData() & CellValue::IsEmpty;
	}
	int RelativeCell::IsMaxPiece() const{
		return GetData() & CellValue::IsMax;
	}
	int RelativeCell::IsFlipped() const{
		return GetData() & CellValue::IsFlipped;
	}

	vector<RelativeCell> RelativeCell::GetSurroundingCells() const{
		vector<RelativeCell> tiles;
		tiles.push_back(RelativeCell(_cell->GetLeft(), _converter));
		tiles.push_back(RelativeCell(_cell->GetTop(), _converter));
		tiles.push_back(RelativeCell(_cell->GetRight(), _converter));
		tiles.push_back(RelativeCell(_cell->GetBottom(), _converter));
		return tiles;
	}
}