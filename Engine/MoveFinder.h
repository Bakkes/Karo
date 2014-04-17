#include "Board.h"
#include "Move.h"

#pragma once
namespace engine{
class MoveFinder
{
public:
	MoveFinder(void);
	~MoveFinder(void);


	std::vector<Move> FindMove(Tile<int>,Tile<int>);

};

}