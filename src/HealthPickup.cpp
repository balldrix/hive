#include "HealthPickup.h"

#include "Camera.h"
#include "Graphics.h"
#include "Pickup.h"
#include "Sprite.h"

#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <string>

void HealthPickup::Init(const std::string& id,
	const Vector2& position,
	Camera* camera,
	Texture* texture)
{
	m_position = position;
	m_camera = camera;

	m_sprite = new Sprite();
	m_sprite->Init(texture);
	m_sprite->SetOrigin(Vector2(8.0f, 9.5f));
	m_sprite->SetColour(Colors::Blue.v);
}

void HealthPickup::Update(float deltaTime)
{
	m_sprite->SetPosition(m_position - m_camera->GetPosition());
}

void HealthPickup::Render(Graphics* graphics)
{
	m_sprite->SetDepth(m_position.y / graphics->GetBackbufferHeight() - 0.1f);
	m_sprite->Render(graphics);
}

void HealthPickup::ApplyEffect()
{
}

void HealthPickup::Shutdown()
{
	delete m_sprite;
	m_sprite = nullptr;
}