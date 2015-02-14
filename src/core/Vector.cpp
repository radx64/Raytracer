#include "Vector.hpp"
#include <cmath>
#include <iostream>

namespace rt
{
namespace core
{

Vector Vector::crossProduct(const Vector& v)
{
	double x = y_ * v.getZ() - v.getY() * z_; 
	double y = z_ * v.getX() - v.getZ() * x_; 
	double z = x_ * v.getY() - v.getX() * y_; 

	return Vector(x, y, z);
}

void Vector::normalize()
{
	double length;
	length = sqrt((x_ * x_) + (y_ * y_) + (z_ * z_));
	x_ /= length;
	y_ /= length;
	z_ /= length;
}

bool Vector::isZero()
{
	if ((0 == x_) && (0 == y_) && (0 == z_))
	{
		return true;
	}
	return false;
}


Vector Vector::operator + (Point& p)
{
	return Vector(x_ +p.getX(), y_ + p.getY(), z_ + p.getZ());
}

}  // namespace core
}  // namespace rt