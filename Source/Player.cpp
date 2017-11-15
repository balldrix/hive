#include "Player.h"
#include "Sprite.h"
#include "Resources.h"
#include "Bullet.h"

Player::Player() :
	m_playerState(IDLE)
{
}

Player::~Player()
{
}

void
Player::Update(float deltaTime)
{
	m_sprite->SetPosition(m_position);

	// Update Bullets
	/*for (int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	{
		if (m_bullet[index]->GetActive())
		{
			m_bullet[index]->Update(deltaTime);
		}
	}

	///////////////////////////////////////////
	// handle bullets delay
	///////////////////////////////////////////

	if (m_firedGun)
	{
		m_shootingTimer -= deltaTime;
	}

	if (m_shootingTimer < 0)
	{
		m_firedGun = false;
	}

	///////////////////////////////////////////

	///////////////////////////////////////////
	// handle melee delay
	///////////////////////////////////////////
	if (m_isMelee)
	{
		m_meleeTimer -= deltaTime;
	}

	if (m_meleeTimer < 0)
	{
		m_isMelee = false;
	}
*/
	///////////////////////////////////////////
}

void Player::Render(Graphics* graphics)
{
	m_sprite->Render(graphics);

	/*
	for(int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	{
	m_bullet[index].Render();
	}

	if(m_showHitBox)
	{
	RenderHitBox(m_pGraphics, m_collisionBox);
	if(m_isMelee)
	{
	RenderHitBox(m_pGraphics, m_meleeHitBox);
	}
	}
	*/
}

void
Player::Reset()
{
	SetPlayerState(IDLE);
	// SetPosition();
	SetActive(true);

	for (int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	{
		m_bullet[index]->Reset();
	}
}
//
//void
//Player::Shoot()
//{
//	if (!m_firedGun)
//	{
//		m_firedGun = true;
//		m_shootingTimer = SHOOTING_DELAY;
//
//		for (int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
//		{
//
//			if (!m_bullet[index].GetActive())
//			{
//				m_bullet[index].SetActive(true);
//				m_bullet[index].SetFacingDirection(m_facingDirection);
//				m_bullet[index].SetCurrentFrame(0);
//				m_bullet[index].SetAnimDone(false);
//				m_bullet[index].SetCurrentMovementSpeed(BULLET_SPEED);
//
//				if (m_facingDirection == RIGHT)
//				{
//					m_bullet[index].SetPosition(m_position + Vector2(8.0f, 0.0f));
//					m_bullet[index].SetCurrentVelocity(directionNS::RIGHT);
//					m_position.x -= PLAYER_KICKBACK;
//
//				}
//				else
//				{
//					m_bullet[index].SetPosition(m_position - Vector2(8.0f, 0.0f));
//					m_bullet[index].SetCurrentVelocity(directionNS::LEFT);
//					m_position.x += PLAYER_KICKBACK;
//				}
//				m_bullet[index].FlipSprite();
//				break;
//			}
//		}
//	}
//}
//
//void
//Player::Melee()
//{
//	if (!m_isMelee)
//	{
//		m_isMelee = true;
//		m_meleeTimer = MELEE_DELAY;
//
//		//SetAnimState(MELEE);
//
//		// draw swing weapon effect
//	}
//}


void
Player::SetPlayerState(PlayerState state)
{
	m_playerState = state;
}

//void
//Player::SetFiredGun(bool fired)
//{
//	m_firedGun = fired;
//}
//
//void
//Player::SetIsMelee(bool melee)
//{
//	m_isMelee = melee;
//}
//
//void
//Player::SetIsStrafe(bool strafe)
//{
//	m_isStrafe = strafe;
//}
//
//void
//Player::SetActive(bool active)
//{
//	m_active = active;
//}