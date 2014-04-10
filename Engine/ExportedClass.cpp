#include "ExportedClass.h"

namespace karo {
	int ExportedClass::ReturnNumber() {
		return 5;
	}

	char* ExportedClass::ReturnString() {
		return "Hello, World!";
	}
}