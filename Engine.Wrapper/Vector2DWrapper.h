#pragma once

#include "Vector2D.h"

using namespace System;

namespace engine {
namespace wrapper {

public ref class Vector2DWrapper {
public:
	Vector2DWrapper(double x, double y);
	~Vector2DWrapper();

	static bool operator ==(Vector2DWrapper^ a, Vector2DWrapper^ b) {
		return (a->X == b->X && a->Y == b->Y);
	}

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