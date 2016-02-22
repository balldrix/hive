#ifndef _ANIMATEDSPRITE_H_
#define _ANIMATEDSPRITE_H_

#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	virtual ~AnimatedSprite();

	virtual void	Init(Graphics* graphics, TextureManager* textureManager, unsigned int frames, float frameDelay);
	virtual void	Update(float deltaTime);
	virtual	void	Reset();

	void			SetAnimation(unsigned int animation);
	void			SetLoop(bool loop);
	void			SetAnimDone(bool done);
	void			SetRect();

protected:
	float			m_frameDelay;
	unsigned int	m_numOfFrames;
	unsigned int	m_currentAnimation;
	
	bool			m_loop;
	bool			m_animDone;
	
	float			m_frameTime;

};

#endif _ANIMATEDSPRITE_H_