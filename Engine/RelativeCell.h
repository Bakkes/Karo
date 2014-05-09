#pragma once
#include "Cell.h"
#include "CellValue.h"
namespace engine{
	class RelativeAbsoluteConverter;
	class ENGINE_API RelativeCell{
	public:
		RelativeCell(Cell<int>* cell,RelativeAbsoluteConverter* converter);
		RelativeCell(const RelativeCell&);
		~RelativeCell();
		const RelativeCell GetBottom() const;
		const RelativeCell GetRight() const;
		const RelativeCell GetLeft() const;
		const RelativeCell GetTop() const;

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
	inline bool ENGINE_API operator ==(const RelativeCell& l, const RelativeCell& r){
		if(l.GetRelativePosition() != r.GetRelativePosition()){
			return false;
		}
		if(l.GetData() != r.GetData()){
			return false;
		}
		return true;
	}
	inline bool ENGINE_API operator !=(const RelativeCell& l, const RelativeCell& r){return !(l==r);}

}