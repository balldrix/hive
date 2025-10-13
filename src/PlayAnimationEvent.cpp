#include "PlayAnimationEvent.h"

#include "Animator.h"
#include "IEvent.h"
#include "Logger.h"

#include <string>
#include <variant>

PlayAnimationEvent::PlayAnimationEvent(Animator* animator) :
	IEvent()
{
	m_animator = animator;
}

PlayAnimationEvent::~PlayAnimationEvent()
{
}

void PlayAnimationEvent::OnStart(EventArgument arg)
{
	if(!std::holds_alternative<std::string>(arg))
	{
		Logger::LogError("[PlayAnimationEvent] [OnStart] Incorrect argument, must be a string");
		return;
	}

	std::string stateName = std::get<std::string>(arg);
	m_animator->SetAnimation(stateName);
	m_hasStarted = true;
}

void PlayAnimationEvent::OnUpdate(float deltaTime)
{
	if(m_animator->IsDone()) m_isComplete = true;
}
