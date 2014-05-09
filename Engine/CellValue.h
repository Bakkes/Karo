#pragma once
namespace engine {
	enum CellValue{
		HasTile = 1,
		IsEmpty = 2,
		IsMax = 4,
		IsFlipped = 8
	};
}