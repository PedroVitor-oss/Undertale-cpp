#ifndef VECTOR_H
#define VECTOR_H


class Vector
{
	public:
		float X;
		float Y;

		Vector(float x,float y);
		SetPosition(float x,float y);
		Vector2 operator+(const Vector2 otherVec);


	protected:

	private:
};

#endif // VECTOR_H
