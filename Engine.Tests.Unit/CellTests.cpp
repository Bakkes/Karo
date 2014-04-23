#include <CppUnitTest.h>
#include "Cell.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests {
	TEST_CLASS(CellTests) {
	public:
		// Tests if deleting a cell and its copy doesn't delete garbage.
		// If this test fails, make sure the copy constructor copies everything
		// it needs to copy and the destructor properly deletes everything.
		TEST_METHOD(CopyConstructorMakesCopyOfReferences) {
			// Create one cell.
			engine::Cell<int> *cellOld = new engine::Cell<int>(new engine::Vector2D());

			// Copy the cell.
			engine::Cell<int> *cellNew = new engine::Cell<int>(*cellOld);

			// Delete both. If the copy constructor works properly, this won't cause errors.
			delete cellOld;
			delete cellNew;
		}
	};
}