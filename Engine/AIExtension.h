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
		virtual void Start(const int& maxDepth);
		// notify the exntension taht minmax ends
		virtual void End();

		// go one ply deeper, allows extension to do plystep initilization
		virtual void Step(const Players& player, const int& currentDepth, EvalResult&);

		// allows extension to do move ordering
		virtual void UpdateMoves(const int& depth,std::vector<Move>& moves);
		// allows extension to do pruning
		virtual bool ShouldContinue(const EvalResult& currentResult, EvalResult& prevResult, const Players& player);

	protected:
		int GetMaxDepth() const;
	private:
		int _maxDepth;

	};


}