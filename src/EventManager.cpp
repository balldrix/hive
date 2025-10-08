#include "EventManager.h"

#include "IEvent.h"
#include "Logger.h"

#include <fmt/core.h>
#include <string>
#include <unordered_map>

void EventManager::RegisterEvent(const std::string& name, IEvent* event)
{
	if(m_eventRegistry.contains(name))
	{
		Logger::LogWarning(fmt::format("[EventManager] [RegisterEvent] Event with name {} already registered", name));
		return;
	}

	m_eventRegistry[name] = event;
}

void EventManager::UnRegisterEvent(const std::string& name)
{
	if(m_eventRegistry.find(name) == m_eventRegistry.end())
	{
		Logger::LogWarning(fmt::format("[EventManager] [GetEvent] Event with name {} not registered.", name));
	}

	delete m_eventRegistry[name];
	m_eventRegistry[name] = nullptr;
	m_eventRegistry.erase(name);
}

IEvent* EventManager::GetEvent(const std::string& name)
{
	if(m_eventRegistry.find(name) == m_eventRegistry.end())
	{
		Logger::LogWarning(fmt::format("[EventManager] [GetEvent] Event with name {} not registered.", name));
		return nullptr;
	}

	return m_eventRegistry[name];
}