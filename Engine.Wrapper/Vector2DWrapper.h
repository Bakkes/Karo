#pragma once

#include "Vector2D.h"

using namespace System;

namespace engine {
namespace wrapper {
<<<<<<< HEAD
ref class Vector2DWrapper
=======
public ref class Vector2DWrapper
>>>>>>> master
{
public:
	Vector2DWrapper(double x, double y);
	~Vector2DWrapper();
	property double X
	{
		double get();
		void set(double);
	}

	property double Y
	{
		double get();
		void set(double);
	}
private:
	Vector2D * _vector2D;
};

}
}