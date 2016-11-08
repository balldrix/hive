#include "AABB.h"

AABB::AABB() :
	m_min(0.0f, 0.0f),
	m_max(0.0f, 0.0f)
{
}

AABB::AABB(const Vector2 & min, const Vector2 & max)
{
	// set min and max vectors
	m_min = min;
	m_max = max;
}

AABB::~AABB()
{
}

void
AABB::Reset()
{
	// reset vectors to zero
	m_min.Zero;
	m_max.Zero;
}

void
AABB::SetAABB(const AABB &hitbox)
{
	// set min and max vectors
	m_min = hitbox.m_min;
	m_max = hitbox.m_max;
}

void
AABB::SetAABB(const Vector2 &min, const Vector2 &max)
{
	// set min and max vectors
	m_min = min;
	m_max = max;
}

void
AABB::OffSetAABB(float x, float y)
{
	// offset min and max x values
	m_min.x += x;
	m_max.x += x;

	// offset min and max y values
	m_min.y += y;
	m_max.y += y;
}

void 
AABB::OffSetAABB(Vector2 offSet)
{
	// off set min and max values
	m_min += offSet;
	m_max += offSet;
}

void
AABB::SetMin(const Vector2 &min)
{
	m_min = min; // set min
}

void 
AABB::SetMax(const Vector2 &max)
{
	m_max = max; // set max
}

bool
AABB::Collision(const AABB &other) const
{
	// check if min and max points fall outside other bounding box
	// if they always fall outside they will be no collision 
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
	// set min and max values
	m_min = other.m_min;
	m_max = other.m_max;
	return *this;
}