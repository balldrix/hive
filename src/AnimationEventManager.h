#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <variant>

using EventArgument = std::variant<float, std::string>;

class AnimationEventManager
{
public:
	using EventCallback = std::function<void(EventArgument)>;
	static AnimationEventManager* s_instance;

	static void Init();
	static void Destroy();

	static void RegisterEvent(const std::string& name, EventCallback callback);
	static void UnRegisterEvent(const std::string& name);
	static void TriggerEvent(const std::string& name, EventArgument arg);

private:
	AnimationEventManager() {};
	~AnimationEventManager();

	void Shutdown();

	static std::unordered_map<std::string, EventCallback> s_eventRegistry;
};