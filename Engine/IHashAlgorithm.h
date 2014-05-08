#include <string>
#include "Move.h"
#include "Cell.h"

namespace engine{


	class IHashAlgorithm{

	public :
		virtual int hash(Board) =0;

	};
}