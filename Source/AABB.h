// AABB.h
// Christopher Ball 2018
// axis aligned bounding box
// for 2D collision detection

#ifndef _AABB_H_
#define _AABB_H_

#include "pch.h"

class AABB
{
public:
	AABB();
	AABB(const Vector2 &min, const Vector2 &max);
	~AABB();
	
	// helper methods
	void				SetAABB(const AABB &hitbox); // set hit box to new aabb points
	void				SetAABB(const Vector2 &min, const Vector2 &max); // set min and max bounds
	void				OffSetAABB(float x, float y); // offset min and max
	void				OffSetAABB(Vector2 offSet); // offset min and max
	void				SetMin(const Vector2 &min); // set min vector
	void				SetMax(const Vector2 &max); // set max vector

	const Vector2&		GetMin() const { return m_min; } // get min vector
	const Vector2&		GetMax() const { return m_max; } // get max vector

	bool				Collision(const AABB &other) const; // return true if collision occurs with other
	virtual void		Reset(); // reset min and max to zero

	AABB&				operator=(const AABB &other); // = operator overload

private:
	Vector2				m_min; // min vector point
	Vector2				m_max; // max vector point
};

#endif _AABB_H_