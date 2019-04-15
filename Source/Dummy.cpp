#include "Dummy.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "Resources.h"
#include "ControlSystem.h"

#include "DummyOwnedStates.h"

Dummy::Dummy() :
	m_currentState(nullptr),
	m_previousState(nullptr),
	m_globalState(nullptr)
{}

Dummy::~Dummy()
{
}

void Dummy::Init(const Vector2& position, SpriteSheet* sprite, Animator* animator, HitBoxManager* hitBoxManager)
{
	m_sprite = sprite;
	m_position = position;
	m_animator = animator;
	m_animator->SetAnimation(0);
	m_hitBoxManager = hitBoxManager;
}

void 
Dummy::Update(float deltaTime)
{
	// TODO update player state machine
	m_globalState->Execute(this);
	m_currentState->Execute(this);

	// update object
	GameObject::Update(deltaTime);
}

void
Dummy::Render(Graphics* graphics)
{
	// render enemy sprite
	if(m_animator)
	{
		m_sprite->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation()->spriteSheetIndex);
	}
	else
	{
		m_sprite->Render(graphics, 0);
	}

	// render hitbox
	m_hitBoxManager->Render(graphics);
}

void
Dummy::Reset()
{
	// set enemy state back to Idle
	SetEnemyState(DummyIdleState::Instance());

	// Set Position 
	// TODO set world position and screen position
	SetPosition(DummyStartScreenPositionX, DummyStartScreenPositionY);

	// reset hitboxes
	m_hitBoxManager->SetCurrentHitBox(0);

	SetActive(true);
}

void Dummy::SetEnemyState(State<Dummy>* state)
{
	assert(m_currentState && state);

	// store previous state
	m_previousState = m_currentState;

	// call on exit for current state
	m_currentState->OnExit(this);

	// set new state
	m_currentState = state;

	// call on entry for new state
	m_currentState->OnEnter(this);
}

void Dummy::ReturnToPreviousState()
{
	SetEnemyState(m_previousState);
}
