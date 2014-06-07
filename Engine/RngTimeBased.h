#pragma once
#include <list>
#include "IRng.h"

namespace engine { 

	class ENGINE_API RngTimeBased : public IRng {

	public:
		RngTimeBased();
		virtual ~RngTimeBased();

		long long NextInteger() override;

	private:
		long long CreateLong();

		std::list<int>* _returnedNumbers;

	};

}