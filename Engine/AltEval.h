#pragma once

#include "IStaticEvaluation.h"
#include "RelativeCell.h"
#include "DllImportExport.h"

namespace engine {
	class ENGINE_API AltEval : public IStaticEvaluation {
	public:
		AltEval(void);
		~AltEval(void);
		int Eval(IBoard* board, Players player) override;
	private:
		int CalcScoreFor(RelativeCell &cell, Players player);
		int CalcScoreWithNext(RelativeCell &cell, Players player,
			const RelativeCell&(AltEval::*GetNext)(RelativeCell&));
		int CalcDownScore(RelativeCell &cell, Players player);
		int CalcDownRightScore(RelativeCell &cell, Players player);
		int CalcTopRightScore(RelativeCell &cell, Players player);

		const RelativeCell &GetLeft(RelativeCell &current);
		const RelativeCell &GetRight(RelativeCell &current);
		const RelativeCell &GetTop(RelativeCell &current);
		const RelativeCell &GetBottom(RelativeCell &current);

		const RelativeCell &GetTopLeft(RelativeCell &current);
		const RelativeCell &GetTopRight(RelativeCell &current);
		const RelativeCell &GetBottomLeft(RelativeCell &current);
		const RelativeCell &GetBottomRight(RelativeCell &current);
	};
}