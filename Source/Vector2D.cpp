#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D() :
x(0.0f),
y(0.0f)

{}

Vector2D::Vector2D(float vX, float vY) :
x(vX),
y(vY)
{
}

Vector2D::Vector2D(const Vector2D &v) :
x(v.x),
y(v.y)
{
}

Vector2D::~Vector2D()
{
}

Vector2D&
Vector2D::Zero()
{
	x = 0;
	y = 0;
	return *this;
}

Vector2D
Vector2D::operator + (const Vector2D &v) const
{
	Vector2D temp;
	temp.x = x + v.x;
	temp.y = y + v.y;
	return temp;
}

Vector2D
Vector2D::operator - (const Vector2D &v) const
{
	Vector2D temp;
	temp.x = x - v.x;
	temp.y = y - v.y;
	return temp;
}

Vector2D
Vector2D::operator -()
{
	Vector2D temp;
	temp.x = -x;
	temp.y = -y;
	return temp;
} 

Vector2D
Vector2D::operator * (float scale) const
{
	Vector2D temp;
	temp.x = x * scale;
	temp.y = y * scale;
	return temp;
}

Vector2D
Vector2D::operator / (float scale) const
{
	Vector2D temp;
	temp.x = x / scale;
	temp.y = y / scale;
	return temp;
}

Vector2D&
Vector2D::operator = (const Vector2D &v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2D&
Vector2D::operator += (const Vector2D &v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2D&
Vector2D::operator -= (const Vector2D &v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2D&
Vector2D::operator++ ()
{
	x++;
	y++;
	return *this;
}

Vector2D
Vector2D::operator ++ (int)
{
	Vector2D temp(*this);
	++*this;
	return temp;
}

Vector2D&
Vector2D::operator-- ()
{
	x--;
	y--;
	return *this;
}

Vector2D
Vector2D::operator -- (int)
{
	Vector2D temp(*this);
	--*this;
	return temp;
}

bool 
Vector2D::operator > (const Vector2D &v) const
{
	if (this->x > v.x && this->y > v.y)
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool 
Vector2D::operator < (const Vector2D &v) const
{
	if (this->x < v.x && this->y < v.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Vector2D
Vector2D::Inverse() const
{
	Vector2D temp;
	temp.x = -this->x;
	temp.y = -this->y;

	return temp;
}

float
Vector2D::Length() const
{
	float length;
	length = sqrt(x*x + y*y);
	return length;
}

float
Vector2D::LengthSqr() const
{
	float length;
	length = (x*x + y*y);
	return length;
}

float
Vector2D::Dot(const Vector2D &v) const
{
	float dot;
	dot = (x * v.x + y * v.y);
	return dot;
}

Vector2D
Vector2D::Normalised() const
{
	Vector2D normalised;
	normalised = (*this) / Length();
	return normalised;
}

