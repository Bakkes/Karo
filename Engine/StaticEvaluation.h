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
		int PlayingPhase(int score, IBoard* board, RelativeCell it, Players players);
		int PlayingPhaseFriendlyMax(int score, IBoard* board, RelativeCell it, Players players);
		int PlayingPhaseFriendlyMin(int score, IBoard* board, RelativeCell it, Players players);
		int PlayingPhaseHostileMax(int score, IBoard* board, RelativeCell it, Players players);
		int PlayingPhaseHostileMin(int score, IBoard* board, RelativeCell it, Players players);
		int PlacingPhase(int score, IBoard* board, RelativeCell it, Players players);
		int PlacingPhaseFriendly(int score, IBoard* board, RelativeCell it, Players players);
		int PlacingPhaseHostile(int score, IBoard* board, RelativeCell it, Players players);
	};
}
