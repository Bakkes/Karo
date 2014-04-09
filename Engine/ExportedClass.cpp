#include "ExportedClass.h"

namespace Engine {
	int ExportedClass::ReturnNumber() {
		return 5;
	}

	char* ExportedClass::ReturnString() {
		return "Hello, World!";
	}
}