#pragma once

#include "IStaticEvaluation.h"
#include "DllImportExport.h"

namespace engine {
	class ENGINE_API AltEval : public IStaticEvaluation {
	public:
		AltEval(void);
		~AltEval(void);
		int Eval(IBoard* board, Players player) override;
	private:
		int CalcScoreFor(RelativeCell &cell, Players player);
		int CalcRightScore(RelativeCell &cell, Players player);
		int CalcDownScore(RelativeCell &cell, Players player);
		int CalcDownRightScore(RelativeCell &cell, Players player);
		int CalcTopRightScore(RelativeCell &cell, Players player);
	};
}