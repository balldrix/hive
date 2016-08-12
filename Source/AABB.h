#ifndef _AABB_H_
#define _AABB_H_

#include "Vector2D.h"

class AABB
{
public:
	AABB();
	~AABB();
	
	virtual void		Reset();

	const Vector2D&		GetMin() const { return m_min; }
	const Vector2D&		GetMax() const { return m_max; }
	
	void				SetAABB(const Vector2D &min, const Vector2D &max);
	void				OffSetAABB(float x, float y);
	void				SetMin(const Vector2D &min);
	void				SetMax(const Vector2D &max);

	bool				Collision(const AABB &other) const;

	AABB&				operator=(const AABB &other);

private:
	Vector2D			m_min;
	Vector2D			m_max;
};

#endif _AABB_H_