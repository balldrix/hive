#include "AABB.h"

AABB::AABB() :
	m_min(0.0f,0.0f),
	m_max(0.0f,0.0f)
{
}

AABB::~AABB()
{
}

void
AABB::Reset()
{
	m_min.Zero();
	m_max.Zero();
}

void
AABB::SetAABB(const Vector2D &min, const Vector2D &max)
{
	m_min = min;
	m_max = max;
}

void
AABB::OffSetAABB(float x, float y)
{
	m_min.x += x;
	m_max.x += x;

	m_min.y += y;
	m_max.y += y;
}

void
AABB::SetMin(const Vector2D &min)
{
	m_min = min;
}

void 
AABB::SetMax(const Vector2D &max)
{
	m_max = max;
}

bool
AABB::Collision(const AABB &other) const
{
	if (m_max.x < other.m_min.x || m_min.x > other.m_max.x)
	{
		return false;
	}

	if(m_max.y < other.m_min.y || m_min.y > other.m_max.y)
	{
		return false;
	}
	
	return true;
}

AABB&
AABB::operator = (const AABB &other)
{
	m_min = other.m_min;
	m_max = other.m_max;
	return *this;
}