#include "Pickup.h"

#include "Camera.h"
#include "Graphics.h"
#include "Sprite.h"

#include <directxtk/SimpleMath.h>
#include <string>

Pickup::Pickup() :
	m_position(Vector2::Zero),
	m_camera(nullptr),
	m_sprite(nullptr)
{
}

Pickup::~Pickup()
{
	Shutdown();
}

void Pickup::Init(const std::string& id,
	const Vector2& position,
	Camera* camera,
	Texture* texture, Color colour)
{
	m_position = position;
	m_camera = camera;

	m_sprite = new Sprite();
	m_sprite->Init(texture);
	m_sprite->SetOrigin(Vector2(8.0f, 9.5f));
	m_sprite->SetColour(colour);
}

void Pickup::Update(float deltaTime)
{
	m_sprite->SetPosition(m_position - m_camera->GetPosition());
}

void Pickup::Render(Graphics* graphics)
{
	m_sprite->SetDepth(m_position.y / graphics->GetBackbufferHeight() - 0.1f);
	m_sprite->Render(graphics);
}


void Pickup::Shutdown()
{
	delete m_sprite;
	m_sprite = nullptr;
}