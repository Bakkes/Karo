#pragma once
#pragma warning(disable:4251)

#include <iostream>
#include <time.h>
#include <hash_map>
#include "Board.h"
#include "IHashAlgorithm.h"



namespace engine {
	class ENGINE_API ZobristHashing : public IHashAlgorithm {

	public:
		ZobristHashing();
		virtual ~ZobristHashing();

		void ExecuteMove(const Move&) override;
		void UndoMove(const Move&) override;

		int GetHash() const override;

	private:
		int _hashValues[16][400];
		int _currentHash;
	};
}