#include <string>
#include "Move.h"
#include "Cell.h"

namespace engine{


	class ENGINE_API IHashAlgorithm {

	public :
		virtual ~IHashAlgorithm() {
		}

		virtual int GetHash() = 0;

	};
}