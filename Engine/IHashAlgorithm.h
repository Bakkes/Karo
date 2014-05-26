#include <string>
#include "Move.h"
#include "Cell.h"

namespace engine{


	class ENGINE_API IHashAlgorithm {

	public :
		virtual ~IHashAlgorithm() {
		}

		virtual void ExecuteMove(const Move&) = 0;
		virtual void UndoMove(const Move&) = 0;

		virtual int GetHash() const = 0;

	};
}