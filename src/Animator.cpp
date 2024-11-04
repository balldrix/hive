#include "Animator.h"

#include "AnimationData.h"
#include "AnimatedSpriteData.h"
#include "Logger.h"
#include "SpriteFrameData.h"

#include <string>

Animator::Animator() :
	m_currentAnimation(),
	m_animatedSpriteData(),
	m_paused(false),
	m_currentFrame(0),
	m_animDone(false),
	m_animationTimer(0.0f)
{
}

void Animator::Init(AnimatedSpriteData animatedSpriteData)
{
	m_animatedSpriteData = animatedSpriteData;
	SetAnimation(0);
}

void Animator::Update(float deltaTime)
{
	if(m_paused)
		return;

	m_animationTimer += deltaTime;

	SpriteFrameData frameData = m_animatedSpriteData.spriteFrameData[m_currentAnimation.from + m_currentFrame];
	float duration = (float)frameData.duration * .001f;

	if(m_animationTimer > duration)
	{
		m_animationTimer = 0;

		if(!m_animDone)
		{
			m_currentFrame++;

			if(m_currentFrame < m_currentAnimation.frameCount)
				return;

			if(m_currentAnimation.loop)
			{
				m_currentFrame = 0;
				return;
			}

			m_currentFrame = m_currentAnimation.frameCount - 1;
			m_animDone = true;
		}
	}
}

void Animator::SetAnimation(unsigned int index)
{
	m_currentAnimation = m_animatedSpriteData.animationData[index];
	m_animDone = false;
}

void Animator::SetAnimation(const std::string& name)
{
	AnimationData newAnimation;

	for(AnimationData data : m_animatedSpriteData.animationData)
	{
		if(data.name == name)
		{
			m_currentAnimation = data;
			m_animDone = false;
			return;
		}
	}

	std::string error = "[Animator.cpp] Error! No animation with name " + name + " found. Check animation data.";
	Logger::LogError(error);
}

void Animator::Reset()
{
	m_animationTimer = 0.0f;
	m_animDone = false;
	m_currentFrame = 0;
}