#include "Collider.h"

#include "AABB.h"
#include "Graphics.h"
#include "Sprite.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>

Collider::Collider() :
	m_position(Vector2::Zero),
	m_colour(Colors::White),
	m_flipped(false),
	m_sprite(nullptr)
{
}

Collider::~Collider()
{
}

// initialise the hit box
void Collider::Init(Sprite* sprite, Color colour)
{
	// init sprite
	m_sprite = new Sprite(*sprite);
	m_sprite->SetColour(colour);
	m_sprite->SetAlpha(0.25f);

	m_colour = colour;

	m_sprite->SetOrigin(Vector2::Zero);
}

// update hitbox
void Collider::Update(const Vector2& position)
{
	// update bounding box and position
	m_position = position;
}

void Collider::Render(Graphics* graphics)
{
	AABB box = m_boundingBox;

	if(m_flipped)
	{
		box = FlipAABB();
	}

	box.OffSetAABB(m_position);

	RECT rect;
	rect.left = (LONG)box.GetMin().x;
	rect.top = (LONG)box.GetMin().y;
	rect.right = (LONG)box.GetMax().x;
	rect.bottom = (LONG)box.GetMax().y;

	m_sprite->SetDepth(1.0f);
	m_sprite->Render(graphics, m_position, rect);
}

void Collider::Render(Graphics* graphics, const Vector2& position)
{
	AABB box = m_boundingBox;

	if(m_flipped)
	{
		box = FlipAABB();
	}

	box.OffSetAABB(position);

	// set sprite rect
	RECT rect = {};
	rect.left = (LONG)box.GetMin().x;
	rect.top = (LONG)box.GetMin().y;
	rect.right = (LONG)box.GetMax().x;
	rect.bottom = (LONG)box.GetMax().y;

	m_sprite->SetDepth(1.0f);
	m_sprite->Render(graphics, position, rect);
}

float Collider::GetLeft()
{
	AABB box = m_boundingBox;

	if(m_flipped)
	{
		box = FlipAABB();
	}

	box.OffSetAABB(m_position);

	return box.GetMin().x;
}

float Collider::GetWidth()
{
	AABB box = m_boundingBox;

	if(m_flipped)
	{
		box = FlipAABB();
	}

	box.OffSetAABB(m_position);

	return (box.GetMax() - box.GetMin()).x;
}

float Collider::GetTop()
{
	AABB box = m_boundingBox;

	if(m_flipped)
	{
		box = FlipAABB();
	}

	box.OffSetAABB(m_position);

	return box.GetMin().y;
}

float Collider::GetHeight()
{
	AABB box = m_boundingBox;

	if(m_flipped)
	{
		box = FlipAABB();
	}

	box.OffSetAABB(m_position);

	return (box.GetMax() - box.GetMin()).y;
}

void Collider::SetAABB(const AABB& boundingBox)
{
	m_boundingBox = boundingBox;
}

void Collider::SetFlipped(bool flipped)
{
	m_flipped = flipped;
}

AABB Collider::FlipAABB()
{
	Vector2 newMin = m_boundingBox.GetMin();
	Vector2 newMax = m_boundingBox.GetMax();
	AABB newBox = m_boundingBox;

	newMin.x = m_boundingBox.GetMax().x * -1;
	newMax.x = m_boundingBox.GetMin().x * -1;

	newBox.SetAABB(newMin, newMax);

	return newBox;
}

AABB Collider::FlipAABB(const AABB& box)
{
	Vector2 newMin = box.GetMin();
	Vector2 newMax = box.GetMax();
	AABB newBox;

	newMin.x = box.GetMax().x * -1;
	newMax.x = box.GetMin().x * -1;

	newBox.SetAABB(newMin, newMax);

	return newBox;
}

// return true if collision with other hitbox
bool Collider::OnCollision(const Collider &collider)
{
	AABB box = m_boundingBox;
	
	if(m_flipped)
	{
		box = FlipAABB();
	}

	AABB otherBox = collider.GetAABB();

	if(collider.m_flipped)
	{
		otherBox = FlipAABB(otherBox);
	}

	box.OffSetAABB(m_position);
	otherBox.OffSetAABB(collider.m_position);

	if(box.Collision(otherBox))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// return true if collision with position
bool Collider::OnCollision(const Vector2 &position)
{
	AABB box = m_boundingBox;

	if(m_flipped)
	{
		box = FlipAABB();
	}

	box.OffSetAABB(m_position);

	if(box.Collision(position))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Collider::Delete()
{
	delete m_sprite;
	m_sprite = nullptr;
}
