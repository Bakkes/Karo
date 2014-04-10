#pragma once

#include "DllImportExport.h"

namespace engine {
	class ExportedClass {
	public:
		static ENGINE_API int ReturnNumber();
		static char* ReturnString();
	};
}