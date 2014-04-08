#pragma once

#include "MyMath.h"

namespace Karo
{
	double MyMath::Add(double a, double b) {
		return a + b;
	}

	double MyMath::Power(double base, double power) {
		double result = base;
		for (int i = 0; i < power; i++) {
			result *= base;
		}
		return result;
	}
}