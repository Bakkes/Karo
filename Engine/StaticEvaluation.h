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
		int PlayingFase(const RelativeCell& it);
		int CalculateMovePhase(const RelativeCell& it);
		int PlacingFase(const RelativeCell& it);
		int CalculatePlacing(const RelativeCell& it);
		bool IsLinable(const RelativeCell& what, const int& player);
		IBoard* _board;
	};
}
