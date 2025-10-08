#include "WaitEvent.h"

#include "IEvent.h"
#include "Logger.h"

#include <variant>

WaitEvent::WaitEvent() :
	m_timer(0.0f)
{
}

void WaitEvent::OnStart(EventArgument arg)
{
	if(!std::holds_alternative<float>(arg))
	{
		Logger::LogError("[WaitEvent] [OnStart] Incorrect argument for WaitEvent, must be float");
		return;
	}

	m_timer = std::get<float>(arg);
	m_hasStarted = true;
	m_isComplete = false;
}

void WaitEvent::OnUpdate(float deltaTime)
{
	m_timer -= deltaTime;

	if(m_timer > 0) return;
	m_isComplete = true;
}

void WaitEvent::Reset()
{
	m_hasStarted = false;
	m_isComplete = false;
	m_timer = 0.0f;
}
