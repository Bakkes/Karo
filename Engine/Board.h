#include "Grid.h"
#include "IBoard.h"
#pragma once
namespace engine{

	class ENGINE_API Board : public IBoard{
	public:
		Board();
		~Board();
		void ExecuteMove(Move *m, Players player) override;
		std::vector<Move>* GetLegalMoves(Players player) override;
		std::vector<Tile<int>>* GetOccupiedTiles() override;
	private:
		Grid<int>* _grid;
	};

}
