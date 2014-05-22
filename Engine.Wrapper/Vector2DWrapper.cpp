#include "Vector2DWrapper.h"

namespace engine {
namespace wrapper {

Vector2DWrapper::Vector2DWrapper(double x, double y)
{
	_vector2D = new Vector2D(x, y);
}

Vector2DWrapper::~Vector2DWrapper()
{
	this->!Vector2DWrapper();
}

Vector2DWrapper::!Vector2DWrapper()
{
	delete _vector2D;
	_vector2D = nullptr;
}

double Vector2DWrapper::X::get()
{
	return _vector2D->X();
}

void Vector2DWrapper::X::set(double value)
{
	_vector2D->X(value);
}

double Vector2DWrapper::Y::get()
{
	return _vector2D->Y();
}

void Vector2DWrapper::Y::set(double value)
{
	_vector2D->Y(value);
}

}
}