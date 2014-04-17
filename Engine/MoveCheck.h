#include "Board.h"
#include "Vector2D.h"
#pragma once

namespace engine{
	enum CheckDirection{ LEFT, RIGHT , DOWN, UP , LEFTUP, LEFTDOWN, RIGHTUP,RIGHTDOWN, 
		JUMPLEFT,JUMPRIGHT,JUMPDOWN,JUMPUP,JUMPLEFTUP,JUMPLEFTDOWN,JUMPRIGHTUP,JUMPRIGHTDOWN};
	//각각경우에 대해 1. 보드가 잇나없나
	//2. 있다 -> 말이있나확인
	//3. 말이 있다: 점프된곳에 말이있나확인, 있으면 false, 없으면 true
	//4. 말이 없다 : true
	//5. 1.보드가없다 -> 보드다른데꺼 떼와서 옮길수있나 체크 
	// 되면 true 
class MoveCheck
{
public:
	MoveCheck(void);
	~MoveCheck(void);
	int CheckTile(int a);
	CheckDirection GetCheckDirection();
	TileValue getTile();
	Vector2D getPosition();

private :
	CheckDirection _checkDirection;
	TileValue _tile;
	
	bool possibilityMove;
	Vector2D position;
};

}