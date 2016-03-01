#include "Player.h"
#include "Resources.h"

Player::Player() : 
AnimatedSprite(),
Transform(),
m_pGraphics(NULL),
m_pPlayerTexture(NULL),
m_collisionBox(AABB()),
m_meleeHitBox(AABB()),
m_playerState(IDLE),
m_shootingTimer(0.0f),
m_meleeTimer(0.0f),
m_firedGun(false),
m_isMelee(false),
m_isStrafe(false),
m_active(false)
{
}

Player::~Player()
{

}

void
Player::Init(Graphics* graphics, TextureManager* playerTexture, TextureManager* bulletTexture)
{
	m_pGraphics = graphics;
	m_pPlayerTexture = playerTexture;

	m_tileSize = { 32, 32 };

	AnimatedSprite::Init(m_pGraphics, m_pPlayerTexture, NUM_PLAYER_ANIM_FRAMES, PLAYER_ANIM_FRAME_DELAY);

	for(int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	{
		m_bullet[index].Init(m_pGraphics, bulletTexture);
	}

	m_currentMovementSpeed = PLAYER_WALK_SPEED;
	
	m_collisionBox.SetAABB(m_position, m_position + Vector2D(m_tileSize.x, m_tileSize.y));

	m_meleeHitBox = m_collisionBox;
		
	SetPosition(START_X, START_Y);

	m_shootingTimer = SHOOTING_DELAY;
	m_meleeTimer = MELEE_DELAY;
	
	m_isLerper = true;
}

void
Player::Update(float deltaTime)
{
	AnimatedSprite::Update(deltaTime);
	AnimatedSprite::FlipSprite();
	Transform::Update(deltaTime);
	
	// set collision box for melee attack
	m_meleeHitBox = m_collisionBox;

	if(m_facingDirection == RIGHT)
	{
		m_meleeHitBox.OffSetAABB(m_tileSize.x / 2, 0.0f);
	}
	else
	{
		m_meleeHitBox.OffSetAABB((m_tileSize.x / 2) * -1, 0.0f);
	}

	// Update Bullets
 	for (int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	{
		if(m_bullet[index].GetActive())
		{
			m_bullet[index].Update(deltaTime);
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
	if(m_isMelee)
	{ 
		m_meleeTimer -= deltaTime;
	}

	if(m_meleeTimer < 0)
	{
		m_isMelee = false;
	}
	///////////////////////////////////////////
}

void
Player::Render()
{
	Sprite::Render(m_position, m_spriteData.rect);

	for (int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	{
		m_bullet[index].Render();
	}

	//if(m_showHitBox)
	//{
	//	RenderHitBox(m_pGraphics, m_collisionBox);
	//	if(m_isMelee)
	//	{
	//		RenderHitBox(m_pGraphics, m_meleeHitBox);
	//	}
	//}
}

void
Player::Reset()
{
	Transform::Reset();
	AnimatedSprite::Reset();

	SetPlayerState(IDLE);
	SetPosition(START_X, START_Y);
	SetActive(true);

	for(int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	{
		m_bullet[index].Reset();
	}
}

void
Player::Shoot()
{
	if (!m_firedGun)
	{
		m_firedGun = true;
		m_shootingTimer = SHOOTING_DELAY;

		for (int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
		{
			
			if (!m_bullet[index].GetActive())
			{
				m_bullet[index].SetActive(true);
				m_bullet[index].SetFacingDirection(m_facingDirection);
				m_bullet[index].SetCurrentFrame(0);
				m_bullet[index].SetAnimDone(false);
				m_bullet[index].SetCurrentMovementSpeed(BULLET_SPEED);
				
				if (m_facingDirection == RIGHT)
				{
					m_bullet[index].SetPosition(m_position + Vector2D(8.0f, 0.0f));
					m_bullet[index].SetCurrentVelocity(directionNS::RIGHT);
					m_position.x -= PLAYER_KICKBACK;

				}
				else
				{
					m_bullet[index].SetPosition(m_position - Vector2D(8.0f, 0.0f));
					m_bullet[index].SetCurrentVelocity(directionNS::LEFT);
					m_position.x += PLAYER_KICKBACK;
				}
				m_bullet[index].FlipSprite();
				break;
			}
		}
	}
}

void 
Player::Melee()
{
	if(!m_isMelee)
	{
		m_isMelee = true;
		m_meleeTimer = MELEE_DELAY;
		
		//SetAnimState(MELEE);
		
		// draw swing weapon effect
	}
}

void 
Player::SetPlayerState(PLAYER_STATE state)
{
	m_playerState = state;
}

void
Player::SetFiredGun(bool fired)
{
	m_firedGun = fired;
}

void
Player::SetIsMelee(bool melee)
{
	m_isMelee = melee;
}

void
Player::SetIsStrafe(bool strafe)
{
	m_isStrafe = strafe;
}

void
Player::SetActive(bool active)
{
	m_active = active;
}