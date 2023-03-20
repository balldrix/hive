#include "Particle.h"

#include "Spritesheet.h"
#include "Animator.h"
#include "Graphics.h"

Particle::Particle() : 
	m_spritesheet(nullptr),
	m_animator(nullptr),
	m_position(0.0f, 0.0f),
	m_isActive(false)
{
}

Particle::~Particle()
{
}

void Particle::Init(Spritesheet* spritesheet, Animator* animator)
{
	m_spritesheet = spritesheet;
	m_animator = animator;
}

void Particle::Render(Graphics* graphics)
{
	if(!m_isActive)
		return;

	auto framenum = m_animator->GetCurrentFrame();
	m_spritesheet->SetDepth(1.0f);
	m_spritesheet->Render(graphics, m_position, framenum);
}

void Particle::Update(float deltaTime)
{
	if(!m_isActive)
		return;

	m_animator->Update(deltaTime);

	if(m_animator->IsDone())
		m_isActive = false;
}

void Particle::Emit(const Vector2& position)
{
	m_isActive = true;
	m_position = position;
	m_animator->Reset();
}
