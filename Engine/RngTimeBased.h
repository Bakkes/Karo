#pragma once
#include <list>
#include "IRng.h"

namespace engine { 

	class RngTimeBased : public IRng {

	public:
		RngTimeBased();
		virtual ~RngTimeBased();

		int NextInteger() override;

	private:
		std::list<int>* _returnedNumbers;

	};

}