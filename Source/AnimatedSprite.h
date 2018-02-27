// AnimatedSprite.h
// Christopher Ball 2018
// child of sprite class for animations

#ifndef _ANIMATED_SPRITE_H_
#define _ANIMATED_SPRITE_H_

#include "pch.h"
#include "Sprite.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	virtual ~AnimatedSprite();

	void Init(Graphics* graphics, Texture* texture, 
			  unsigned int frames, float frameDelay, 
			  unsigned int frameWidth, unsigned int frameHeight);
	void Update(float deltaTime);
	void SetAnimation(unsigned int animation);
	void SetLoop(bool loop);
	void SetAnimDone(bool done);
	void SetRect();
	void Reset();

protected:
	float			m_frameDelay;
	unsigned int	m_numOfFrames;
	unsigned int	m_currentAnimation;
	unsigned int	m_currentFrame;

	bool			m_loop;
	bool			m_animDone;

	float			m_frameTime;
	float			m_timeElapsed;

	int				m_frameWidth;
	int				m_frameHeight;
};

#endif // _ANIMATED_SPRITE_H_
