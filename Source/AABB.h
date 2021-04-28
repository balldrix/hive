#pragma once

#include "pch.h"

class AABB
{
public:
	AABB();
	AABB(const Vector2 &min, const Vector2 &max);
	~AABB();
	
	void				SetAABB(const AABB &hitbox); 
	void				SetAABB(const Vector2 &min, const Vector2 &max);
	void				OffSetAABB(float x, float y);
	void				OffSetAABB(Vector2 offSet); 
	void				SetMin(const Vector2 &min); 
	void				SetMax(const Vector2 &max); 

	const Vector2&		GetMin() const { return m_min; }
	const Vector2&		GetMax() const { return m_max; }

	bool				Collision(const AABB &other) const;
	bool				Collision(const Vector2 &other) const; 
	virtual void		Reset(); 

	AABB&				operator=(const AABB &other);

private:
	Vector2				m_min; 
	Vector2				m_max; 
};