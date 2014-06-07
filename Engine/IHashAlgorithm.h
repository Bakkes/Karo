#include <string>
#include <gmp.h>
#include "Move.h"
#include "Cell.h"
#include "IBoard.h"
#include "BigInteger.h"

namespace engine{


	class ENGINE_API IHashAlgorithm {

	public :
		virtual ~IHashAlgorithm() {
		}

		virtual void UpdateBoard(IBoard* board) = 0;
		virtual BigInteger GetHash() = 0;

	};
}