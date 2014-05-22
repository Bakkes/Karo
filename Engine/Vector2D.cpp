#include "Vector2D.h"
namespace engine {
	Vector2D::Vector2D(void)
	{
		init(0,0);
	}

	Vector2D::Vector2D(double x, double y){
		init(x, y);
	}
	Vector2D::Vector2D(double both){
		init(both, both);
	}
	Vector2D::Vector2D(const Vector2D& cpy){
		assert(cpy != null);
		init(cpy._x, cpy._y);
	}
	Vector2D::~Vector2D(void)
	{
	}
	void Vector2D::init(double x, double y){
		_x = x;
		_y = y;
	}
	double Vector2D::X() const{
		return _x;
	}
	double Vector2D::Y() const{
		return _y;
	}
	void Vector2D::X(const double x){
		_x = x;
	}
	void Vector2D::Y(const double y){
		_y = y;
	}
	Vector2D& Vector2D::operator=(Vector2D rhs){
		swap(rhs);
		return *this;
	}

	Vector2D& Vector2D::operator+=(const Vector2D& rhs){
		this->_x += rhs._x;
		this->_y += rhs._y;
		return *this;
	}
	Vector2D& Vector2D::operator-=(const Vector2D& rhs){
		this->_x -= rhs._x;
		this->_y -= rhs._y;
		return *this;
	}
	Vector2D& Vector2D::operator*=(const Vector2D& rhs){
		this->_x *= rhs._x;
		this->_y *= rhs._y;
		return *this;
	}
	Vector2D& Vector2D::operator/=(const Vector2D& rhs){
		this->_x /= rhs._x;
		this->_y /= rhs._y;
		return *this;
	}
}