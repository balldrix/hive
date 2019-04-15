#include "DummyEnemy.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "Resources.h"
#include "ControlSystem.h"

#include "DummyEnemyOwnedStates.h"

DummyEnemy::DummyEnemy() :
	m_currentState(nullptr),
	m_previousState(nullptr),
	m_globalState(nullptr)
{}

DummyEnemy::~DummyEnemy()
{
}

void DummyEnemy::Init(const Vector2& position, HitBoxManager* hitBoxManager, SpriteSheet* sprite, Animator* animator)
{
	m_sprite = sprite;
	m_position = position;
	m_animator = animator;
	m_animator->SetAnimation(0);
	m_hitBoxManager = hitBoxManager;
}

void 
DummyEnemy::Update(float deltaTime)
{
	// TODO update player state machine
	m_globalState->Execute(this);
	m_currentState->Execute(this);

	// update object
	GameObject::Update(deltaTime);
}

void
DummyEnemy::Render(Graphics* graphics)
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
DummyEnemy::Reset()
{
	// set enemy state back to Idle
	SetEnemyState(DummyEnemyIdleState::Instance());

	// Set Position 
	// TODO set world position and screen position
	SetPosition(StartScreenPositionX, StartScreenPositionY);

	// reset hitboxes
	m_hitBoxManager->SetCurrentHitBox(0);

	SetActive(true);
}

void DummyEnemy::SetEnemyState(State<DummyEnemy>* state)
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

void DummyEnemy::ReturnToPreviousState()
{
	SetPlayerState(m_previousState);
}
