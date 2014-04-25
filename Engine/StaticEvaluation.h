#pragma once
#include "IStaticEvaluation.h"
#include "DllImportExport.h"
namespace engine {
	class ENGINE_API StaticEvaluation : public IStaticEvaluation
	{
	public:
		StaticEvaluation(void);
		~StaticEvaluation(void);
		int Eval(IBoard*, Players);
	private:
		int flippedValue;
		int blockedTileValue;
		int cornerValue;
		int neighborValue;
		int lineValue;
	};
}
