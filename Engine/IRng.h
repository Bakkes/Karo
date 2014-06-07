#pragma once

#include "DllImportExport.h"

namespace engine {

	class ENGINE_API IRng {

	public:
		virtual IRng::~IRng() {
		}

		virtual long long NextInteger() = 0;

	};

}
