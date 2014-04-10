#include "Size.h"

namespace karo {
	Size::Size(unsigned  width,unsigned  height) : Vector2D((double) width,(double) height) {}

	Size::Size() : Vector2D(0,0) {}
	Size::Size(const Size& ref): Vector2D(ref){}
	Size::Size (const Vector2D& ref) : Vector2D(ref){}
	void Size::SetHeight(unsigned height) {
		this->Y(height);
	}

	unsigned  Size::GetHeight() const {
		return (unsigned) this->Y();
	}

	void Size::SetWidth(unsigned _width) {
		this->X(_width);
	}

	unsigned  Size::GetWidth() const {
		return (unsigned) this->X();
	}
}
