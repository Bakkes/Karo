#pragma once
#include "Cell.h"
#include "CellValue.h"
#include "RelativeAbsoluteConverter.h"
namespace engine{
	class RelativeCell{
	public:
		RelativeCell(Cell<int>* cell,RelativeAbsoluteConverter* converter);
		RelativeCell(const RelativeCell&);
		~RelativeCell();
		RelativeCell GetBottom() const;
		RelativeCell GetRight() const;
		RelativeCell GetLeft() const;
		RelativeCell GetTop() const;

		const Vector2D& GetAbsolutePosition() const;
		const Vector2D& GetRelativePosition() const;
		const int& GetData() const;

		const int& HasTile() const;
		const int& IsEmpty() const;
		const int& IsMaxPiece() const;
		const int& IsFlipped() const;

		vector<RelativeCell> GetSurroundingCells() const;

	private:
		Cell<int>* _cell;
		RelativeAbsoluteConverter* _converter;
		Init(Cell<int>* cell, RelativeAbsoluteConverter* converter);
	};
}