#pragma once

#include <DirectXMath.h>
#include <functional>
#include <string>
#include <unordered_map>
#include <variant>

struct SpawnNPCArgument
{
	std::string id;
	std::string definitionId;
	DirectX::XMFLOAT2 position;
};

using EventArgument = std::variant<float, std::string, DirectX::XMFLOAT2, SpawnNPCArgument>;

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
