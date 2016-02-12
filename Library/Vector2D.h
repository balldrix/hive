#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D &vector);
	~Vector2D();

	// reset vector to (0,0)
	Vector2D& Zero();

	// operator overloads
	Vector2D operator + (const Vector2D &v) const;
	Vector2D operator - ();
	Vector2D operator - (const Vector2D &v) const;
	Vector2D operator * (float scale) const;
	Vector2D operator / (float scale) const;
	Vector2D& operator = (const Vector2D &v);
	Vector2D& operator += (const Vector2D &v);
	Vector2D& operator -= (const Vector2D &v);
	Vector2D& operator ++ ();
	Vector2D operator ++ (int);
	Vector2D& operator -- ();
	Vector2D operator -- (int);
	bool operator > (const Vector2D &v) const;
	bool operator < (const Vector2D &v) const;

	Vector2D Inverse() const;

	// get length of vector
	float Length() const;

	// compare length without square root
	float LengthSqr() const;

	// get dot product of vector
	float Dot(const Vector2D &v) const;

	// normalise a vector
	Vector2D Normalised() const;

	// get x
	float GetX() { return x; }

	// get y
	float GetY() { return y; }

	// x, y variables
	float x;
	float y;
};


#endif _VECTOR2D_H_