#pragma once

#include <string>
#include <unordered_map>

#include "IEvent.h"

class EventManager
{
public:
	EventManager() {};
	~EventManager() {};

	void RegisterEvent(const std::string& name, IEvent* event);
	void UnRegisterEvent(const std::string& name);
	IEvent* GetEvent(const std::string& name);

private:
	std::unordered_map<std::string, IEvent*> m_eventRegistry;
};
