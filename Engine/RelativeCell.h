#pragma once
#include "Cell.h"
namespace Engine{
	class RelativeCell {
	public:

		RelativeCell(Cell<int>* cell);

	private:
		Cell<int> _cell;

	};
}