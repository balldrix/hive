#include "Dummy.h"
#include "Graphics.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "Resources.h"
#include "ControlSystem.h"

#include "DummyOwnedStates.h"

Dummy::Dummy() : 
	m_stateMachine(nullptr),
	m_health(0)
{}

Dummy::~Dummy()
{
	if(m_stateMachine)
	{
		delete m_stateMachine;
		m_stateMachine = nullptr;
	}
}

void Dummy::Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager)
{
	m_sprite = sprite;
	m_shadow = shadow;
	m_position = position;
	m_animator = animator;
	m_animator->SetAnimation(0);
	m_hitBoxManager = hitBoxManager;
	m_hitBoxManager->SetCurrentHitBox(0);

	m_stateMachine = new StateMachine<Dummy>(this);
	m_stateMachine->Init(DummyIdleState::Instance(), nullptr, nullptr);

	m_health = 4;
}

void 
Dummy::Update(float deltaTime)
{
	// update state machine
	m_stateMachine->Update();

	// update object
	GameObject::Update(deltaTime);
}

void
Dummy::Render(Graphics* graphics)
{
	// render shadow first
	if(m_shadow)
	{
		m_shadow->SetDepth(m_position.y / graphics->GetHeight());
		m_shadow->Render(graphics);
	}

	if(m_sprite)
	{
		m_sprite->SetDepth(m_position.y / graphics->GetHeight());

		// render enemy sprite
		if(m_animator)
		{
			m_sprite->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation()->spriteSheetIndex);
		}
		else
		{
			m_sprite->Render(graphics, 0);
		}
	}

	// render hitbox
	//if(m_hitBoxManager)
	//{
	//	m_hitBoxManager->Render(graphics);
	//}
}

void
Dummy::Reset()
{
	// set enemy state back to Idle
	m_stateMachine->ChangeState(DummyIdleState::Instance());

	// Set Position 
	// TODO set world position and screen position
	SetPosition(DummyStartScreenPositionX, DummyStartScreenPositionY);

	// reset hitboxes
	m_hitBoxManager->SetCurrentHitBox(0);

	SetActive(true);
}

void Dummy::ApplyDamage(int amount)
{
	m_health -= amount;

	if(m_health < 1)
	{
		m_stateMachine->ChangeState(DummyDeadState::Instance());
	}
	else
	{
		m_stateMachine->ChangeState(DummyHurtState::Instance());
	}
}
