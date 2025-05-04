#include "EventManager.h"

#include "Logger.h"

#include <fmt/core.h>
#include <string>
#include <unordered_map>

EventManager* EventManager::s_instance = nullptr;
std::unordered_map<std::string, EventManager::EventCallback> EventManager::s_eventRegistry;

void EventManager::Init()
{
	Logger::LogInfo("Initialising Animation Event Manager.");

	s_instance = new EventManager();
}

void EventManager::Destroy()
{
	delete s_instance;
	s_instance = nullptr;
}

void EventManager::RegisterEvent(const std::string& name, EventCallback callback)
{
	if(s_eventRegistry.contains(name))
	{
		Logger::LogWarning(fmt::format("[EventManager] [RegisterEvent] Event with name {} already registered", name));
		return;
	}

	s_eventRegistry[name] = callback;
}

void EventManager::UnRegisterEvent(const std::string& name)
{
	s_eventRegistry.erase(name);
}

void EventManager::TriggerEvent(const std::string& name, EventArgument arg)
{
	if(s_eventRegistry.find(name) == s_eventRegistry.end())
	{
		Logger::LogWarning(fmt::format("[EventManager] [TriggerEvent] Event with name {} not registered.", name));
		return;
	}

	s_eventRegistry[name](arg);
}

EventManager::~EventManager()
{
	Shutdown();
}

void EventManager::Shutdown()
{
	s_eventRegistry.clear();
}
