#pragma once
#include "Vector2D.h"
namespace engine {
	// a positive size of somthing
	// just an extension of vector
	class Size : public Vector2D{
	public:
		// set size to 0,0
		Size();
		// set size to width, height
		Size(unsigned  width,unsigned  height);
		Size(const Size&);
		// conversion from Vector2D (constructor):
		Size (const Vector2D&);
		// conversion from Vector2D (assignment):
		Size& operator= (const Vector2D& x) {
			init(x.X(), x.Y());
			return *this;
		}
		void SetHeight(unsigned);
		unsigned  GetHeight() const;
		void SetWidth(unsigned);
		unsigned  GetWidth() const;
		operator Vector2D() {return Vector2D(X(), Y());}
	};

}
