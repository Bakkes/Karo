#pragma once
#include "Grid.h"
#include "CellValue.h"
#include "Size.h"
using namespace std;
namespace engine{
	class RelativeAbsoluteConverter{
	public:
		RelativeAbsoluteConverter();
		RelativeAbsoluteConverter(Grid<int>* parseable);
		RelativeAbsoluteConverter(Grid<int>* parseable, Vector2D topleft);
		~RelativeAbsoluteConverter();
		Vector2D ToRelative(const Vector2D&)const;
		Vector2D ToAbsolute(const Vector2D&)const; 
		// allows the converter to be kept up to date with board
		void MoveTile(const Vector2D& from, const Vector2D& to);
		Vector2D CalcShiftCorrection(const Vector2D&,const Vector2D&) const;
		int GetWidth();
		int GetHeight();
	private:
		void Init(Grid<int>* parseable, Vector2D tl);
		// the absolute topleft
		Vector2D _topLeft;

		// amount of tiles per row
		vector<int> _rowTileCount;

		// amount of tiles per collumn
		vector<int> _colTileCount;
		Vector2D& WrapArround(Vector2D& input) const;

		int GridWidth() const;
		int GridHeight() const;
	};
}