#pragma once

#include "IEvent.h"

#include <string>
#include <unordered_map>
#include <utility>

using EventKey = std::pair<std::string, std::string>;

struct EventKeyHash {
	size_t operator()(const EventKey& key) const
	{
		return std::hash<std::string>()(key.first) ^ std::hash<std::string>()(key.second);
	}
};

class EventManager
{
public:
	EventManager() {};
	~EventManager();

	void RegisterEvent(const std::string& eventName, const std::string& targetId, IEvent* event);
	void UnRegisterEvent(EventKey key);
	void UnRegisterAllForTarget(const std::string& targetId);
	IEvent* GetEvent(EventKey key);

private:
	bool HasKey(const EventKey& key) const { return m_eventRegistry.contains(key); }

	std::unordered_map<EventKey, IEvent*, EventKeyHash> m_eventRegistry;
};
