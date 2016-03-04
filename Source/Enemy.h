#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Constants.h"
#include "Randomiser.h"
#include "Transform.h"
#include "AnimatedSprite.h"
#include "AABB.h"

const unsigned int	ENEMY_ANIM_NUM_FRAMES	= 1;
const float			ENEMY_ANIM_FRAME_DELAY	= 1.0f;
const unsigned int	ENEMY_ANIM_FRAME_WIDTH	= 32;
const unsigned int	ENEMY_ANIM_FRAME_HEIGHT = 32;
const unsigned int	ENEMY_ROAM_SPEED		= 64;
const unsigned int	ENEMY_RUN_SPEED			= 32;
const float			AI_THINKING_TIME		= 30.0f;

class Enemy : public Transform, public AnimatedSprite, public AABB
{
public:

	enum ENEMY_STATE
	{
		ENEMY_STATE_IDLE,
		ENEMY_STATE_ROAM,
		ENEMY_STATE_DEAD,
		ENEMY_STATE_ATTACKING,
		ENEMY_STATE_DEATH,
		ENEMY_STATE_MAX_STATES
	};

	Enemy();
	virtual ~Enemy();

	void				Init(Graphics* graphics, TextureManager* enemyTexture);
	void				Update(float deltaTime);
	void				Render();
	void				Reset();
	
	//	methods to proces ai states
	ENEMY_STATE			Idle();
	ENEMY_STATE			Roam();
	ENEMY_STATE			Attack();
	ENEMY_STATE			Die();
	ENEMY_STATE			Dead();

	///////////////////////////////
	
	ENEMY_STATE			GetEnemyState() const { return m_enemyState; }
	bool				GetIsActive() const { return m_active; }

	void				SetEnemyState(ENEMY_STATE state);
	void				SetRandomDirection();
	void				SetActive(bool active);

private:
	Graphics*			m_pGraphics;
	TextureManager*		m_pEnemyTexture;

	const char*			m_ID;
	ENEMY_STATE			m_enemyState;
	float				m_aiTimer;
	bool				m_active;
};

#endif _ENEMY_H_