#include <string>
#include "Move.h"
#include "Cell.h"
#include "IBoard.h"

namespace engine{


	class ENGINE_API IHashAlgorithm {

	public :
		virtual ~IHashAlgorithm() {
		}

		virtual void UpdateBoard(IBoard* board) = 0;
		virtual void ExecuteMove(const Move& move) = 0;
		virtual void UndoMove(const Move& move, Players player) = 0;
		virtual long long GetHash() = 0;

	};
}