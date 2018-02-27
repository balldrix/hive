#include "Player.h"
#include "AnimatedSprite.h"
#include "Resources.h"
#include "UnitVectors.h"

Player::Player() :
	m_playerState(IDLE)
{
}

Player::~Player()
{
}

void Player::Init(Sprite* sprite, Vector2 position)
{
	m_sprite = sprite;
	m_position = position;
	m_acceleration = PLAYER_ACCELERATION;
	m_deceleration = PLAYER_DECELERATION;
	m_movementSpeed = PLAYER_WALK_SPEED;
}

void Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	m_sprite->SetPosition(m_position);
}

void Player::Render(Graphics* graphics)
{
	m_sprite->Render(graphics);
}

void Player::Reset()
{
	SetPlayerState(IDLE);
	// SetPosition();
	SetActive(true);
}

void Player::Move(Controller::Buttons button)
{
	switch(button)
	{
	case Controller::up:
		SetTargetVelocityY(Direction::UP.y);
		break;
	case Controller::down:
		SetTargetVelocityY(Direction::DOWN.y);
		break;
	case Controller::left:
		SetTargetVelocityX(Direction::LEFT.x);
		break;
	case Controller::right:
		SetTargetVelocityX(Direction::RIGHT.x);
		break;
	default:
		break;
	}
}

void Player::Stop(Controller::Buttons button)
{
	switch(button)
	{
	case Controller::up:
		// stop Y movement
		SetTargetVelocityY(0.0f);
		break;
	case Controller::down:
		// stop Y movement
		SetTargetVelocityY(0.0f);
		break;
	case Controller::left:
		// stop X movement
		SetTargetVelocityX(0.0f);
		break;
	case Controller::right:
		// stop X movement
		SetTargetVelocityX(0.0f);
		break;
	default:
		break;
	}
}

void Player::SetPlayerState(PlayerState state)
{
	m_playerState = state;
}