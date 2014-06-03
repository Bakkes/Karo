#pragma once

#include "DllImportExport.h"

namespace engine {

	class ENGINE_API IRng {

	public:
		virtual IRng::~IRng() {
		}

		virtual int NextInteger() = 0;
		virtual long long NextLongLong() = 0;

	};

}
