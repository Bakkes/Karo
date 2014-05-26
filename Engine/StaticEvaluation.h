#pragma once
#include "IStaticEvaluation.h"
#include "DllImportExport.h"

namespace engine {
	class ENGINE_API StaticEvaluation : public IStaticEvaluation
	{
	public:
		StaticEvaluation(void);
		~StaticEvaluation(void);
		int Eval(IBoard*, Players) override;
	private:
		int _flippedValue;
		int _blockedTileValue;
		int _cornerValue;
		int _cornerValue2;
		int _neighborValue;
		int _lineValue;
		int _centerValue;
		int _semiCenterValue;
		int _centerColumnValue;
		int _bottomOrTopRowValue;
		int PlayingFase(int score, IBoard* board, RelativeCell it, Players players);
		int PlayingFaseFriendlyMax(int score, IBoard* board, RelativeCell it, Players players);
		int PlayingFaseFriendlyMin(int score, IBoard* board, RelativeCell it, Players players);
		int PlayingFaseHostileMax(int score, IBoard* board, RelativeCell it, Players players);
		int PlayingFaseHostileMin(int score, IBoard* board, RelativeCell it, Players players);
		int PlacingFase(int score, IBoard* board, RelativeCell it, Players players);
		int PlacingFaseFriendly(int score, IBoard* board, RelativeCell it, Players players);
		int PlacingFaseHostile(int score, IBoard* board, RelativeCell it, Players players);
	};
}
