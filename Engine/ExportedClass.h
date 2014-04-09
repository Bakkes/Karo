#pragma once

#include "DllImportExport.h"

namespace Engine {
	class ExportedClass {
	public:
		static ENGINE_API int ReturnNumber();
		static char* ReturnString();
	};
}