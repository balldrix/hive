#ifndef _BULLET_H_
#define _BULLET_H_

#include "Vector2D.h"
#include "TextureManager.h"
#include "AnimatedSprite.h"
#include "AABB.h"
#include "Transform.h"

const float			BULLET_ANIM_FRAME_DELAY = 0.005f;
const unsigned int	NUM_BULLET_ANIM_FRAMES = 3;
const unsigned int	BULLET_SPEED = 800;

class Bullet : public AnimatedSprite, public Transform, public AABB
{
public:

	enum BULLET_STATE
	{
		STATIC,
		EXPLODING,
		MAX_ANIM_STATES
	};

	Bullet();
	~Bullet();

	void Init(Graphics* graphics, TextureManager* texture);
	void Update(float deltaTime);
	void Render();

	void Reset();

	void SetBulletState(BULLET_STATE state);

	BULLET_STATE		GetBulletState() const { return m_bulletState; }

private:
	Graphics*			m_pGraphics;
	TextureManager*		m_pBulletTexture;
	BULLET_STATE		m_bulletState;
};

#endif _BULLET_H_