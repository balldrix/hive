#include "Animator.h"

#include "AnimatedSpriteData.h"
#include "AnimationEventData.h"
#include "AnimationStateData.h"
#include "EventManager.h"
#include "Logger.h"
#include "SpriteFrameData.h"

#include <string>

Animator::Animator() :
	m_currentAnimation(),
	m_animatedSpriteData(),
	m_paused(false),
	m_currentFrame(0),
	m_animDone(false),
	m_animationTimer(0.0f),
	m_eventManager(nullptr)
{
}

void Animator::Init(AnimatedSpriteData animatedSpriteData, EventManager* eventManager)
{
	m_animatedSpriteData = animatedSpriteData;
	m_eventManager = eventManager;
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
			if(m_currentFrame + 1 < m_currentAnimation.frameCount)
			{
				m_currentFrame++;
			}
			else if(m_currentAnimation.loop)
			{
				m_currentFrame = 0;
			}
			else
			{
				m_currentFrame = m_currentAnimation.frameCount - 1;
				m_animDone = true;
			}
			
			TriggerEvents();
		}
	}
}

void Animator::SetAnimation(unsigned int index)
{
	m_currentAnimation = m_animatedSpriteData.animationStateData[index];
	m_animDone = false;
}

void Animator::SetAnimation(const std::string& name)
{
	AnimationStateData newAnimation;

	for(AnimationStateData data : m_animatedSpriteData.animationStateData)
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

void Animator::TriggerEvents()
{
	int targetFrame = m_currentAnimation.from + m_currentFrame;
	
	auto it = std::find_if(m_animatedSpriteData.animationEventData.begin(), m_animatedSpriteData.animationEventData.end(),
	[&](const AnimationEventData& event) { return event.frameNumber == targetFrame; });

	if(it != m_animatedSpriteData.animationEventData.end()) {
		m_eventManager->TriggerEvent(it->eventName, it->argument);
	}
}
