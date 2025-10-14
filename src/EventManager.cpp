#include "EventManager.h"

#include "IEvent.h"
#include "Logger.h"

#include <fmt/core.h>
#include <string>
#include <unordered_map>
#include <utility>

EventManager::~EventManager()
{
	for(auto& [key, event] : m_eventRegistry) {
		delete event;
	}
	m_eventRegistry.clear();
}

void EventManager::RegisterEvent(const std::string& eventName, const std::string& targetId, IEvent* event)
{
	EventKey key = { eventName, targetId };
	if(HasKey(key))
	{
		Logger::LogWarning(fmt::format("[EventManager] [RegisterEvent] Event {0} for owner {1} already registered", eventName, targetId));
		return;
	}

	m_eventRegistry[key] = event;
}

void EventManager::UnRegisterEvent(EventKey key)
{
	if(!HasKey(key))
	{
		Logger::LogWarning(fmt::format("[EventManager] [UnregisterEvent] Event {0} for owner {1} not registered.", key.first, key.second));
		return;
	}

	delete m_eventRegistry[key];
	m_eventRegistry.erase(key);
}

void EventManager::UnRegisterAllForTarget(const std::string& targetId)
{
	for(auto it = m_eventRegistry.begin(); it != m_eventRegistry.end(); ) {
		if(it->first.second == targetId) {
			delete it->second;
			it = m_eventRegistry.erase(it);
		}
		else {
			++it;
		}
	}
}

IEvent* EventManager::GetEvent(EventKey key)
{
	if(!HasKey(key))
	{
		Logger::LogWarning(fmt::format("[EventManager] [GetEvent] Event {0} for owner {1} not registered.", key.first, key.second));
		return nullptr;
	}

	return m_eventRegistry[key];
}