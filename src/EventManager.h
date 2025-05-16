#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <variant>

using EventArgument = std::variant<float, std::string>;

class EventManager
{
public:
	EventManager() {};
	~EventManager() {};

	using EventCallback = std::function<void(EventArgument)>;

	void RegisterEvent(const std::string& name, EventCallback callback);
	void UnRegisterEvent(const std::string& name);
	void TriggerEvent(const std::string& name, EventArgument arg);

private:
	std::unordered_map<std::string, EventCallback> m_eventRegistry;
};