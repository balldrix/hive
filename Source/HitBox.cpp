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
	m_sprite->SetAlpha(0.3f);
	m_sprite->SetColour(colour);

	m_colour = colour; // store colour variable

	// TODO replace this when hitbox manager is in place
	m_boundingBox.SetAABB(Vector2::Zero, Vector2(16.0f, 16.0f));
}

// update hitbox
void HitBox::Update(const Vector2& position)
{
	// update bounding box and position
	m_position = position;
	m_boundingBox.OffSetAABB(position);
}

// draw hitbox
void HitBox::Render(Graphics* graphics)
{
	// set sprite rect
	RECT box;
	box.left = (LONG)m_boundingBox.GetMin().x;
	box.top = (LONG)m_boundingBox.GetMin().y;
	box.right = (LONG)m_boundingBox.GetMax().x;
	box.bottom = (LONG)m_boundingBox.GetMax().y;

	m_sprite->Render(graphics, m_position, box);
}

void HitBox::SetAABB(const AABB& boundingBox)
{
	m_boundingBox = boundingBox;
}
