#include "Player.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "Resources.h"
#include "ControlSystem.h"

#include "PlayerOwnedStates.h"

Player::Player() :
	m_currentState(PlayerIdleState::Instance()),
	m_previousState(nullptr),
	m_globalState(PlayerGlobalState::Instance())
{
}

Player::~Player()
{

}

void Player::Init(ControlSystem* controlSystem, SpriteSheet* sprite, Animator* animator, const Vector2& position, HitBoxManager* hitBoxManager)
{
	m_controlSystem = controlSystem;
	m_sprite = sprite;
	m_position = position;
	m_acceleration = PlayerAcceleration;
	m_deceleration = PlayerDeceleration;
	m_movementSpeed = WalkSpeed;
	m_animator = animator;
	m_animator->SetAnimation(0);
	m_hitBoxManager = hitBoxManager;
}

void Player::Update(float deltaTime)
{
	// update object
	GameObject::Update(deltaTime);

	// if player has an animator
	if(m_animator)
	{
		// update animator
		m_animator->Update(deltaTime);
	}

	// TODO update player state machine
	m_globalState->Execute(this);
	m_currentState->Execute(this);

	// update position of sprite
	m_sprite->SetPosition(m_position);

	// update hitbox
	m_hitBoxManager->Update();
}

void Player::Render(Graphics* graphics)
{
	// render player sprite
	if(m_animator)
	{
		m_sprite->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation()->spriteSheetIndex);
	}
	else
	{
		m_sprite->Render(graphics, 0);
	}

	// render hitbox
	//m_hitBoxManager->Render(graphics);
}

void Player::Reset()
{
	// set player state back to Idle
	SetPlayerState(PlayerIdleState::Instance());

	// Set Position 
	// TODO set world position and screen position
	SetPosition(StartScreenPositionX, StartScreenPositionY);

	// reset hitboxes
	m_hitBoxManager->SetCurrentHitBox(0);

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

void Player::Move(const Vector2& direction)
{
	// true if switching direction
	if(direction.x < 0 && m_currentVelocity.x > 0 || 
		direction.x > 0 && m_currentVelocity.x < 0)
	{
		// slow down before switching
		SetTargetVelocityX(0.0f);
		return;
	}

	SetTargetVelocity(direction);

	// true if moving to the left
	if(m_currentVelocity.x < 0)
	{
		FlipHorizontally(true);
	}
	
	// true if moving to the right
	if(m_currentVelocity.x > 0)
	{
		FlipHorizontally(false);
	}
}

void Player::Stop()
{
	SetTargetVelocity(Vector2::Zero);
	SetCurrentVelocity(Vector2::Zero);
}

void Player::Punch()
{
	if(m_controlSystem->CanAttack())
	{
		SetPlayerState(PlayerJabState::Instance());
	}
}

void Player::FlipHorizontally(bool flip)
{
	// true if flip param is true
	if(flip == true)
	{
		// flip sprite
		m_sprite->SetFlipEffect(SpriteEffects::SpriteEffects_FlipHorizontally);

	}
	else
	{
		m_sprite->SetFlipEffect(SpriteEffects::SpriteEffects_None);	
	}
	
	// flip hitboxes
	m_hitBoxManager->SetFlipped(flip);
}

