#include "Player.h"
#include "Resources.h"

Player::Player() : 
AnimatedSprite(),
Transform(),
m_pGraphics(NULL),
m_pTextureManager(NULL),
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
Player::Init(Graphics* graphics, TextureManager* textureManager)
{
	m_pGraphics = graphics;
	m_pTextureManager = textureManager;

	AnimatedSprite::Init(m_pGraphics, m_pTextureManager, "PLAYER", PLAYER, NUM_PLAYER_ANIM_FRAMES, PLAYER_ANIM_FRAME_DELAY);

	//m_pBulletSprite = bulletSprite;

	//for(int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	//{
	//	m_bullets[index].Init(bulletSprite);
	//}

	Transform::SetCurrentMovementSpeed(PLAYER_WALK_SPEED);
	
	
	m_collisionBox.SetAABB(m_position, m_position + Vector2D(TILE_SIZE, TILE_SIZE));

	m_meleeHitBox = m_collisionBox;
		
	SetPosition(START_X, START_Y);

	m_shootingTimer = SHOOTING_DELAY;
	m_meleeTimer = MELEE_DELAY;
}

void
Player::Update(float deltaTime)
{
	AnimatedSprite::Update(deltaTime);

	AnimatedSprite::FlipSprite();
	
	// set collision box for melee attack
	m_meleeHitBox = m_collisionBox;

	if(m_facingDirection == RIGHT)
	{
		m_meleeHitBox.OffSetAABB(TILE_SIZE / 2, 0.0f);
	}
	else
	{
		m_meleeHitBox.OffSetAABB((TILE_SIZE / 2) * -1, 0.0f);
	}

	// Update Bullets
 //	for (int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	//{
	//	if(m_bullets[index].IsActive())
	//	{
	//		m_bullets[index].Update(deltaTime);
	//	}
 //	}

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
	Sprite::RenderSprite(m_position, m_spriteData.rect);

	//for (int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	//{
	//	m_bullets[index].Render();
	//}

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
Player::Shoot()
{
	/*if (!m_firedGun)
	{
		m_firedGun = true;
		m_shootingTimer = SHOOTING_DELAY;

		for (int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
		{
			
			if (!m_bullets[index].IsActive())
			{
				m_bullets[index].SetActive(true);
				m_bullets[index].SetFacingDirection(m_facingDirection);
				m_bullets[index].SetCurrentAnimFrame(0);
				m_bullets[index].SetAnimDone(false);
				
				if (m_facingDirection == RIGHT)
				{
					m_bullets[index].SetPosition(m_position + Vector2D(8.0f, 0.0f));
					m_bullets[index].SetCurrentVelocity(directionNS::RIGHT);
					m_position.x -= PLAYER_KICKBACK;

				}
				else
				{
					m_bullets[index].SetPosition(m_position - Vector2D(8.0f, 0.0f));
					m_bullets[index].SetCurrentVelocity(directionNS::LEFT);
					m_position.x += PLAYER_KICKBACK;
				}
				m_bullets[index].FlipSprite(m_bullets[index].GetSprite(), m_facingDirection);
				break;
			}
		}
	}*/
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
Player::Reset()
{
	Transform::Reset();
	AnimatedSprite::Reset();

	SetPlayerState(IDLE);
	SetPosition(START_X, START_Y);
	SetActive(true);

	//for (int index = 0; index < MAX_BULLETS_ON_SCREEN; index++)
	//{
	//	m_bullets[index].SetActive(false);
	//}
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