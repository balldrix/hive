#include "Player.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "Resources.h"

#include "PlayerOwnedStates.h"

Player::Player() :
	m_controlSystem(nullptr),
	m_sprite(nullptr),
	m_animator(nullptr),
	m_currentState(PlayerIdleState::Instance()),
	m_globalState(PlayerGlobalState::Instance())
{
}

Player::~Player()
{
	
}

void Player::Init(ControlSystem* controlSystem, SpriteSheet* sprite, Vector2 position)
{
	m_controlSystem = controlSystem;
	m_sprite = sprite;
	m_position = position;
	m_acceleration = PlayerAcceleration;
	m_deceleration = PlayerDeceleration;
	m_movementSpeed = WalkSpeed;
}

void Player::Init(ControlSystem* controlSystem, SpriteSheet* sprite, Animator* animator, Vector2 position)
{
	Init(controlSystem, sprite, position);
	m_animator = animator;
	m_animator->SetAnimation(0);
}

void Player::Update(float deltaTime)
{
	// if player has an animator
	if(m_animator)
	{
		m_animator->Update(deltaTime);
	}

	GameObject::Update(deltaTime);
	m_sprite->SetPosition(m_position);

	m_globalState->Execute(this);
	m_currentState->Execute(this);
}

void Player::Render(Graphics* graphics)
{
	if(m_animator)
	{
		m_sprite->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation()->spriteSheetIndex);
	}
	else
	{
		m_sprite->Render(graphics, 0);
	}
}

void Player::Reset()
{
	// set player state back to Idle
	SetPlayerState(PlayerIdleState::Instance());

	// Set Position TODO set world position and screen position
	SetPosition(StartScreenPositionX, StartScreenPositionY);
	
	SetActive(true);
}

void Player::SetPlayerState(State<Player>* state)
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

void Player::ReturnToPreviousState()
{
	SetPlayerState(m_previousState);
}
