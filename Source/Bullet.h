#ifndef _BULLET_H_
#define _BULLET_H_

#include "GameObject.h"
#include "Texture.h"
#include "AABB.h"

const float			BULLET_ANIM_FRAME_DELAY = 0.005f;
const unsigned int	BULLET_ANIM_NUM_FRAMES = 3;
const unsigned int	BULLET_ANIM_FRAME_WIDTH = 32;
const unsigned int	BULLET_ANIM_FRAME_HEIGHT = 32;
const unsigned int	BULLET_SPEED = 800;

class Bullet : public GameObject
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

	void				Init(Graphics* graphics, Texture* texture);
	void				Update(float deltaTime);
	void				Render();
	void				Reset();

	void				SetBulletState(BULLET_STATE state);
	void				SetActive(bool active);

	BULLET_STATE		GetBulletState()	const { return m_bulletState; }
	bool				GetActive()			const { return m_active; }

private:
	Graphics*			m_pGraphics;
	Texture*			m_pBulletTexture;
	BULLET_STATE		m_bulletState;
	bool				m_active;
};

#endif _BULLET_H_