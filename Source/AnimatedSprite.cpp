#include "AnimatedSprite.h"
#include "Constants.h"

AnimatedSprite::AnimatedSprite() :
	Sprite(),
	m_frameDelay(1.0f),
	m_numOfFrames(0),
	m_currentAnimation(0),
	m_frameTime(0.0f),
	m_loop(true),
	m_animDone(false)
{
}

AnimatedSprite::~AnimatedSprite()
{

}

void
AnimatedSprite::Init(Graphics* graphics, Texture* texture, 
					 unsigned int frames, float frameDelay, 
					 unsigned int frameWidth, unsigned int frameHeight)
{
	Sprite::Init(texture);

	m_numOfFrames = frames;
	m_frameDelay = frameDelay;

	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;
	SetRect();
}

void
AnimatedSprite::Update(float deltaTime)
{
	m_frameTime -= deltaTime;

	if (m_frameTime < 0)
	{
		m_frameTime = m_frameDelay;

		if (!m_animDone)
		{
			if (m_currentFrame < (m_numOfFrames - 1))
			{
				m_currentFrame++;
			}
			else
			{
				if (m_loop)
				{
					m_currentFrame = 0;
				}
				else
				{
					m_currentFrame = m_numOfFrames - 1;
					m_animDone = true;
				}
			}
		}
		SetRect();
	}
}

void
AnimatedSprite::SetAnimation(unsigned int animation)
{
	m_currentAnimation = animation;
}

void
AnimatedSprite::SetLoop(bool loop)
{
	m_loop = loop;
}

void
AnimatedSprite::SetAnimDone(bool done)
{
	m_animDone = done;
}

void
AnimatedSprite::SetRect()
{
	m_rect.left = m_currentFrame * m_width;
	m_rect.right = m_rect.left + m_width;
	m_rect.top = m_currentAnimation * m_height;
	m_rect.bottom = m_rect.top + m_height;
}

void
AnimatedSprite::Reset()
{
	Sprite::Reset();
	m_animDone = false;
	m_frameTime = 0;
}