#pragma once
#include <algorithm>
#include "DllImportExport.h"
namespace engine {
// base class for cartesian calculations, holds two numbers and suports a lot of operator
// overloads for easy calculations
class ENGINE_API Vector2D {
public:
	Vector2D(const Vector2D&);
	Vector2D(double x, double y);
	Vector2D(double both);
	Vector2D(void);
	~Vector2D(void);
	double X() const;
	double Y() const;
	void X(const double value);
	void Y(const double value);
	void swap(Vector2D& with){
		// enable ADL (not necessary in our case, but good practice)
		using std::swap; 

		// by swapping the members of two classes,
		// the two classes are effectively swapped
		swap(_x, with._x); 
		swap(_y, with._y);
	}
	Vector2D& operator=(Vector2D rhs);
	Vector2D& operator+=(const Vector2D& rhs);
	Vector2D& operator-=(const Vector2D& rhs);
	Vector2D& operator*=(const Vector2D& rhs);
	Vector2D& operator/=(const Vector2D& rhs);
protected:
	// constructors call this
	void init(double x, double y);
private:
	double _x, _y;
};
inline bool operator==(const Vector2D& lhs,const Vector2D& rhs){
	/* do actual comparison */ 
	return lhs.X() == rhs.X() && lhs.Y() == rhs.Y();
}
inline bool operator!=(const Vector2D& lhs, const Vector2D& rhs){return !operator==(lhs,rhs);}
inline bool operator< (const Vector2D& lhs, const Vector2D& rhs){
	/* do actual comparison */
	return lhs.X() * lhs.Y() < rhs.X() * rhs.Y();
}
inline bool operator> (const Vector2D& lhs, const Vector2D& rhs){return  operator< (rhs,lhs);}
inline bool operator<=(const Vector2D& lhs, const Vector2D& rhs){return !operator> (lhs,rhs);}
inline bool operator>=(const Vector2D& lhs, const Vector2D& rhs){return !operator< (lhs,rhs);}
inline Vector2D operator+(Vector2D lhs, const Vector2D& rhs)
{
	lhs += rhs;
	return lhs;
}
inline Vector2D operator-(Vector2D lhs, const Vector2D& rhs)
{
	lhs -= rhs;
	return lhs;
}
inline Vector2D operator*(Vector2D lhs, const Vector2D& rhs)
{
	lhs *= rhs;
	return lhs;
}
inline Vector2D operator/(Vector2D lhs, const Vector2D& rhs)
{
	lhs /= rhs;
	return lhs;
}
}