#include "Players.h"
#include "EvalResult.h"
#include "AIExtension.h"
namespace engine {
	class Pruner : AIExtension{
	public:
		Pruner();
		const bool& ShouldContinue(const EvalResult& evalresult, const Players& player) override;
	};
}