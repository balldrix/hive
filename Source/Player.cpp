#include "Player.h"
#include "AnimatedSprite.h"
#include "Resources.h"

#include "PlayerIdleState.h"
#include "PlayerWalkingState.h"

Player::Player() :
	m_sprite(nullptr),
	m_currentState(PlayerIdleState::Instance())
{
}

Player::~Player()
{
}

void Player::Init(Sprite* sprite, Vector2 position)
{
	m_sprite = sprite;
	m_position = position;
	m_acceleration = PlayerAcceleration;
	m_deceleration = PlayerDeceleration;
	m_movementSpeed = WalkSpeed;
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	m_sprite->SetPosition(m_position);

	m_currentState->Execute(this);
}

void Player::Render(Graphics* graphics)
{
	m_sprite->Render(graphics);
}

void Player::Reset()
{
	// set player state back to Idle
	SetPlayerState(PlayerIdleState::Instance());

	// SetPosition();
	SetPosition(StartScreenPositionX, StartScreenPositionY);
	
	SetActive(true);
}

void Player::SetPlayerState(State<Player>* state)
{
	// call on exit for current state
	m_currentState->OnExit(this);

	// set new state
	m_currentState = state;

	// call on entry for new state
	m_currentState->OnEnter(this);
}