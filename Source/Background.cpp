#include "Background.h"
#include "Sprite.h"
#include "Camera.h"

Background::Background() : m_spriteSheet(nullptr)
{
}

Background::~Background()
{
}

void Background::Update(float deltaTime)
{
	Vector2 screenPosition {};
	screenPosition.x -= m_camera->GetPosition().x;

	if(m_spriteSheet)
	{
		m_spriteSheet->SetPosition(screenPosition);
	}
}

void Background::Init(Sprite* sprite)
{
	m_spriteSheet = sprite;
}

void Background::Render(Graphics* graphics)
{
	m_spriteSheet->Render(graphics);
}

void Background::Reset()
{
}
