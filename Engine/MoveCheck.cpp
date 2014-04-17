#include "MoveCheck.h"

namespace engine{


MoveCheck::MoveCheck(void)
{
}


MoveCheck::~MoveCheck(void)
{
}

int MoveCheck::CheckTile(int a)
{
	
}

Vector2D MoveCheck::getPosition()
{
	return position;
}

CheckDirection MoveCheck::GetCheckDirection()
{
	return _checkDirection;
}

TileValue MoveCheck::getTile()
{
	return _tile;
}


}