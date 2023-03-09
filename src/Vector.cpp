#include "Vector.h"

Vector::Vector(float x,float y)
{
	X = x;
	Y = y;
}
Vector::SetPosition(float x,float y)
{
	X = x;
	Y = y;
}
Vector2 Vector2::operator+(const Vector2 otherVec) {
	Vector2 temp;
	temp.X = X + otherVec.X;
	temp.Y = Y + otherVec.Y;
	return temp;
}
