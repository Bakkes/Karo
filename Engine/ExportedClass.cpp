#include "ExportedClass.h"

namespace engine {
	int ExportedClass::ReturnNumber() {
		return 5;
	}

	char* ExportedClass::ReturnString() {
		return "Hello, World!";
	}
}