#pragma once

#include "IRng.h"

namespace engine { 

	class RngTimeBased : public IRng {

	public:
		RngTimeBased();
		virtual ~RngTimeBased();

		int NextInteger() override;

	};

}