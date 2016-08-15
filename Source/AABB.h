#ifndef _AABB_H_
#define _AABB_H_

#include "pch.h"

class AABB
{
public:
	AABB();
	~AABB();
	
	virtual void		Reset();

	const Vector2&		GetMin() const { return m_min; }
	const Vector2&		GetMax() const { return m_max; }
	
	void				SetAABB(const Vector2 &min, const Vector2 &max);
	void				OffSetAABB(float x, float y);
	void				SetMin(const Vector2 &min);
	void				SetMax(const Vector2 &max);

	bool				Collision(const AABB &other) const;

	AABB&				operator=(const AABB &other);

private:
	Vector2			m_min;
	Vector2			m_max;
};

#endif _AABB_H_