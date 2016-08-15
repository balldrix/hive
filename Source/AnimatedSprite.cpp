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
AnimatedSprite::Init(Graphics* graphics, Texture* textureManager, unsigned int frames, float frameDelay, unsigned int frameWidth, unsigned int frameHeight)
{
	Sprite::Init(graphics, textureManager, frameWidth, frameHeight);

	m_numOfFrames = frames;
	m_frameDelay = frameDelay;

	SetRect();
}

void 
AnimatedSprite::Update(float deltaTime)
{
	m_frameTime -= deltaTime;

	if (m_frameTime < 0)
	{
		m_frameTime = m_frameDelay;

		if(!m_animDone)
		{
			if(m_currentFrame < (m_numOfFrames - 1))
			{
				m_currentFrame++;
			}
			else
			{
				if(m_loop)
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
AnimatedSprite::Reset()
{
	Sprite::Reset();
	m_animDone = false;
	m_frameTime = 0;
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
	m_spriteData.rect.left = m_currentFrame * m_spriteData.width;
	m_spriteData.rect.right = m_spriteData.rect.left + m_spriteData.width;
	m_spriteData.rect.top = m_currentAnimation * m_spriteData.height;
	m_spriteData.rect.bottom = m_spriteData.rect.top + m_spriteData.height;
}