#pragma once
#include "Cell.h"
#include "CellValue.h"
#include "RelativeAbsoluteConverter.h"
namespace engine{
	class ENGINE_API RelativeCell{
	public:
		RelativeCell(Cell<int>* cell,RelativeAbsoluteConverter* converter);
		RelativeCell(const RelativeCell&);
		~RelativeCell();
		RelativeCell GetBottom() const;
		RelativeCell GetRight() const;
		RelativeCell GetLeft() const;
		RelativeCell GetTop() const;

		const Vector2D& GetAbsolutePosition() const;
		Vector2D GetRelativePosition() const;
		int GetData() const;

		int HasTile() const;
		int IsEmpty() const;
		int IsMaxPiece() const;
		int IsFlipped() const;

		vector<RelativeCell> GetSurroundingCells() const;

	private:
		Cell<int>* _cell;
		RelativeAbsoluteConverter* _converter;
		void Init(Cell<int>* cell, RelativeAbsoluteConverter* converter);
	};
}