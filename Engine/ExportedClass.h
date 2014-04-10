#pragma once

#include "DllImportExport.h"

namespace karo {
	class ExportedClass {
	public:
		static ENGINE_API int ReturnNumber();
		static char* ReturnString();
	};
}