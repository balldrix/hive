#include "AnimationEventManager.h"

#include "Logger.h"

#include <fmt/core.h>
#include <string>
#include <unordered_map>

AnimationEventManager* AnimationEventManager::s_instance = nullptr;
std::unordered_map<std::string, AnimationEventManager::EventCallback> AnimationEventManager::s_eventRegistry;

void AnimationEventManager::Init()
{
	Logger::LogInfo("Initialising Animation Event Manager.");

	s_instance = new AnimationEventManager();
}

void AnimationEventManager::Destroy()
{
	delete s_instance;
	s_instance = nullptr;
}

void AnimationEventManager::RegisterEvent(const std::string& name, EventCallback callback)
{
	if(s_eventRegistry.contains(name))
	{
		Logger::LogWarning(fmt::format("[AnimationEventManager] [RegisterEvent] Event with name {} already registered", name));
		return;
	}

	s_eventRegistry[name] = callback;
}

void AnimationEventManager::UnRegisterEvent(const std::string& name)
{
	s_eventRegistry.erase(name);
}

void AnimationEventManager::TriggerEvent(const std::string& name, EventArgument arg)
{
	if(s_eventRegistry.find(name) == s_eventRegistry.end())
	{
		Logger::LogWarning(fmt::format("[AnimationEventManager] [TriggerEvent] Event with name {} not registered.", name));
		return;
	}

	s_eventRegistry[name](arg);
}

AnimationEventManager::~AnimationEventManager()
{
	Shutdown();
}

void AnimationEventManager::Shutdown()
{
	s_eventRegistry.clear();
}
