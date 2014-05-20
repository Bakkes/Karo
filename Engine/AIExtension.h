#pragma once
#include "Players.h"
#include "EvalResult.h"
#include <vector>
namespace engine {
	class AIExtension
	{
	public:
		AIExtension(void);
		virtual ~AIExtension(void);
		// notify the extension that the minmax starts
		virtual void Start();
		// notify the exntension taht minmax ends
		virtual void End();

		// go one ply deeper
		virtual void Step(EvalResult&);

		// allows extension to do move ordering
		virtual void UpdateMoves(std::vector<Move>& moves);
		// allows extension to do pruning
		virtual const bool& ShouldContinue(const EvalResult& evalresult, const Players& player);
	};


}