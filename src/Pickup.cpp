#include "Pickup.h"

#include "AnimatedSpriteData.h"
#include "Animator.h"
#include "Camera.h"
#include "GameDataManager.h"
#include "Graphics.h"
#include "Spritesheet.h"

#include <directxtk/SimpleMath.h>
#include <string>

Pickup::Pickup() :
	m_position(Vector2::Zero),
	m_camera(nullptr),
	m_spritesheet(nullptr),
	m_animator(nullptr)
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

	AnimatedSpriteData spritesheetData = GameDataManager::LoadAnimatedSpriteData("assets\\data\\spritesheets\\pickup_spritesheet.json");
	m_spritesheet = new Spritesheet();
	m_spritesheet->Init(texture, spritesheetData.spriteFrameData);
	m_spritesheet->SetOrigin(Vector2(31.0f, 41.0f));
	m_spritesheet->SetColour(colour);

	m_animator = new Animator();
	m_animator->Init(id, spritesheetData, nullptr);
	m_animator->SetAnimation(0);
}

void Pickup::Update(float deltaTime)
{
	m_animator->Update(deltaTime);
	m_spritesheet->SetPosition(m_position - m_camera->GetPosition());
}

void Pickup::Render(Graphics* graphics)
{
	m_spritesheet->SetDepth(m_position.y / graphics->GetBackbufferHeight() - 0.1f);
	m_spritesheet->Render(graphics, m_animator->GetCurrentFrame());
}

void Pickup::Shutdown()
{
	delete m_spritesheet;
	m_spritesheet = nullptr;
}