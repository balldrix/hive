#include "pch.h"
#include "HitBox.h"
#include "Graphics.h"
#include "Sprite.h"
#include "AABB.h"

HitBox::HitBox() :
	m_position(Vector2::Zero),
	m_colour(Colors::White),
	m_flipped(false)
{
}

HitBox::~HitBox()
{
}

// initialise the hit box
void HitBox::Init(Sprite* sprite, AABB box, Color colour)
{
	// init sprite
	m_sprite = Sprite(*sprite);
	m_sprite.SetColour(colour);
	m_sprite.SetAlpha(0.25f);

	m_colour = colour; // store colour variable

	// set bounding box
	m_boundingBox = box;

	// zero origin
	m_sprite.SetOrigin(Vector2::Zero);
}

// update hitbox
void HitBox::Update(const Vector2& position)
{
	// update bounding box and position
	m_position = position;
}

// draw hitbox
void HitBox::Render(Graphics* graphics)
{
	AABB box = m_boundingBox;

	if(m_flipped)
	{
		box = this->FlipAABB();
	}

	box.OffSetAABB(m_position);

	// set sprite rect
	RECT rect;
	rect.left = (LONG)box.GetMin().x;
	rect.top = (LONG)box.GetMin().y;
	rect.right = (LONG)box.GetMax().x;
	rect.bottom = (LONG)box.GetMax().y;

	m_sprite.Render(graphics, m_position, rect);
}

void HitBox::SetAABB(const AABB& boundingBox)
{
	m_boundingBox = boundingBox;
}

void HitBox::SetFlipped(bool flipped)
{
	m_flipped = flipped;
}

AABB HitBox::FlipAABB()
{
	Vector2 newMin = m_boundingBox.GetMin();
	Vector2 newMax = m_boundingBox.GetMax();
	AABB newBox = m_boundingBox;

	newMin.x = m_boundingBox.GetMax().x * -1;
	newMax.x = m_boundingBox.GetMin().x * -1;

	newBox.SetAABB(newMin, newMax);

	return newBox;
}
