#pragma once

#include "Board.h"
#include "MoveWrapper.h"
#include "PlayersWrapper.h"
#include "CellWrapper.h"
#include "WrapperConversionUtility.h"
#include <vector>

using namespace System;
using namespace System::Collections::Generic;

namespace engine {
namespace wrapper {

public enum class CellValue {
	HasCell = 1,
	IsEmpty = 2,
	IsMax = 4,
	IsFlipped = 8
};

public ref class BoardWrapper
{
public:
	BoardWrapper(void);
	~BoardWrapper(void);
	void ExecuteMove(MoveWrapper^ mw, engine::wrapper::Players player);
	List<CellWrapper^>^ GetOccupiedCells();
	CellWrapper^ GetRelativeCellAt(Vector2DWrapper^ relativePosition);
	IEnumerable<MoveWrapper^>^ GetLegalMoves(Players player);
	void LoadFromString(String^ boardString, int topLeftX, int topLeftY);
	// Gets the C++ Board (unwrapped)
	Board* GetInternalBoard();
	String^ ToString() new;
private:
	Board * _board;
};

}
}
