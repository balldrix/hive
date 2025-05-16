#include "EventManager.h"

#include "Logger.h"

#include <fmt/core.h>
#include <string>
#include <unordered_map>

void EventManager::RegisterEvent(const std::string& name, EventCallback callback)
{
	if(m_eventRegistry.contains(name))
	{
		Logger::LogWarning(fmt::format("[EventManager] [RegisterEvent] Event with name {} already registered", name));
		return;
	}

	m_eventRegistry[name] = callback;
}

void EventManager::UnRegisterEvent(const std::string& name)
{
	m_eventRegistry.erase(name);
}

void EventManager::TriggerEvent(const std::string& name, EventArgument arg)
{
	if(m_eventRegistry.find(name) == m_eventRegistry.end())
	{
		Logger::LogWarning(fmt::format("[EventManager] [TriggerEvent] Event with name {} not registered.", name));
		return;
	}

	m_eventRegistry[name](arg);
}