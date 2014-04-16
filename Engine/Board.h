#include "Grid.h"
#include "IBoard.h"
#include <string>
#pragma once
namespace engine{

	class ENGINE_API Board : IBoard{
	public:
		Board();
		~Board();
		void ExecuteMove(Move *m, Players player) override;
		std::vector<Move>* GetLegalMoves(Players player) override;
		std::vector<Tile<int>>* GetOccupiedTiles() override;
		string ToString();
	private:
		Grid<int>* _grid;
	};

}
