#include "pch.h"
#include "HitBox.h"
#include "Graphics.h"
#include "Sprite.h"
#include "AABB.h"

HitBox::HitBox() :
	m_sprite(nullptr),
	m_position(Vector2::Zero),
	m_colour(Colors::White)
{
}

HitBox::~HitBox()
{
}

// initialise the hit box
void HitBox::Init(Sprite* sprite, Color colour)
{
	// init sprite
	m_sprite = sprite;
	m_sprite->SetAlpha(0.3f);
	m_sprite->SetColour(colour);

	m_colour = colour; // store colour variable

	// TODO replace this when hitbox manager is in place
	m_boundingBox.SetAABB(Vector2(-2.0f, -2.0f), Vector2(6.0f, 16.0f));
	m_sprite->SetOrigin(Vector2::Zero);
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
	box.OffSetAABB(m_position);

	// set sprite rect
	RECT rect;
	rect.left = (LONG)box.GetMin().x;
	rect.top = (LONG)box.GetMin().y;
	rect.right = (LONG)box.GetMax().x;
	rect.bottom = (LONG)box.GetMax().y;

	m_sprite->Render(graphics, m_position, rect);
}

void HitBox::SetAABB(const AABB& boundingBox)
{
	m_boundingBox = boundingBox;
}

AABB HitBox::FlipAABB()
{
	AABB newBox = m_boundingBox;
	newBox.SetMin(newBox.GetMin().X * -1.0f, newBox.GetMin().y * -1.0f);
	newBox.SetMax(newBox.GetMax().X * -1.0f, newBox.GetMax().y * -1.0f);

	return newBox;
}
