#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Transform.h"
#include "Vector2D.h"
#include "AnimatedSprite.h"
#include "Bullet.h"
#include "UnitVectors.h"
#include "Constants.h"
#include "AABB.h"

const unsigned int		PLAYER_ANIM_NUM_FRAMES		= 1;
const float				PLAYER_ANIM_FRAME_DELAY		= 0.3f;
const unsigned int		PLAYER_ANIM_FRAME_WIDTH		= 32;
const unsigned int		PLAYER_ANIM_FRAME_HEIGHT	= 32;
const float				START_X						= 300;
const float				START_Y						= 300;
const unsigned int		PLAYER_WALK_SPEED			= 128;
const unsigned int		PLAYER_RUN_SPEED			= 256;
const unsigned int		MAX_BULLETS_ON_SCREEN		= 64;
const float				SHOOTING_DELAY				= 0.2f;
const float				MELEE_DELAY					= 0.6f;
const float				PLAYER_KICKBACK				= 2.5f;

class Player : public Transform, public AnimatedSprite
{
public:

	enum PLAYER_STATE
	{
		IDLE = 0,
		WALKING,
		RUNNING,
		SHOOTING,
		MELEE,
		MAX_PLAYER_STATES
	};

	Player();
	~Player();

	void				Init(Graphics* graphics, TextureManager* playerTexture, TextureManager* bulletTexture);
	void				Update(float deltaTime);
	void				Render();
						
	void				Shoot();
	void				Melee();

	void				Reset();
						
	void				SetPlayerState(PLAYER_STATE state);
	void				SetFiredGun(bool fired);
	void				SetIsMelee(bool melee);
	void				SetIsStrafe(bool strafe);
	void				SetActive(bool active);

	bool				GetActive()				const { return m_active; }
	PLAYER_STATE		GetState()				const { return m_playerState; }
	bool				GetIsMelee()			const { return m_isMelee; }
	bool				GetIsStrafe()			const { return m_isStrafe; }
	AABB				GetCollisionAABB()		const { return m_meleeHitBox; }
	AABB				GetMeleeAABB()			const { return m_meleeHitBox; }
	Bullet				GetBullet(int index)	const { return m_bullet[index]; }

private:
	Graphics*			m_pGraphics;
	TextureManager*		m_pPlayerTexture;

	AABB				m_collisionBox;
	AABB				m_meleeHitBox;

	PLAYER_STATE		m_playerState;

	float				m_shootingTimer;
	float				m_meleeTimer;
	
	Bullet				m_bullet[MAX_BULLETS_ON_SCREEN];

	bool				m_firedGun;
	bool				m_isMelee;
	bool				m_isStrafe;
	bool				m_active;
	
};

#endif _PLAYER_H_