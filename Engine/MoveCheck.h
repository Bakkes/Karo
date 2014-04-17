#include "Board.h"
#include "Vector2D.h"
#pragma once

namespace engine{
	enum CheckDirection{ LEFT, RIGHT , DOWN, UP , LEFTUP, LEFTDOWN, RIGHTUP,RIGHTDOWN, 
		JUMPLEFT,JUMPRIGHT,JUMPDOWN,JUMPUP,JUMPLEFTUP,JUMPLEFTDOWN,JUMPRIGHTUP,JUMPRIGHTDOWN};
	//������쿡 ���� 1. ���尡 �ճ�����
	//2. �ִ� -> �����ֳ�Ȯ��
	//3. ���� �ִ�: �����Ȱ��� �����ֳ�Ȯ��, ������ false, ������ true
	//4. ���� ���� : true
	//5. 1.���尡���� -> ����ٸ����� ���ͼ� �ű���ֳ� üũ 
	// �Ǹ� true 
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