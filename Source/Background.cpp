#include "Background.h"
#include "Sprite.h"
#include "Camera.h"

Background::Background() : m_sprite(nullptr)
{
}

Background::~Background()
{
}

void Background::Update(float deltaTime)
{
	Vector2 screenPosition {};
	screenPosition.x -= m_camera->GetPosition().x;

	if(m_sprite)
	{
		m_sprite->SetPosition(screenPosition);
	}
}

void Background::Init(Sprite* sprite)
{
	m_sprite = sprite;
}

void Background::Render(Graphics* graphics)
{
	m_sprite->Render(graphics);
}

void Background::Reset()
{
}
