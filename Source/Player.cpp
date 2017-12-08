#include "Player.h"
#include "AnimatedSprite.h"
#include "Resources.h"

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
}

void
Player::Update(float deltaTime)
{
	GameObject::Update(deltaTime);
	m_sprite->SetPosition(m_position);
}

void Player::Render(Graphics* graphics)
{
	m_sprite->Render(graphics);
}

void
Player::Reset()
{
	SetPlayerState(IDLE);
	// SetPosition();
	SetActive(true);
}

void
Player::SetPlayerState(PlayerState state)
{
	m_playerState = state;
}