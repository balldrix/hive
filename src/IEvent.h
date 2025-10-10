#pragma once

#include <DirectXMath.h>
#include <string>
#include <variant>

struct SpawnNPCArgument
{
	std::string id;
	std::string definitionId;
	DirectX::XMFLOAT2 position = DirectX::XMFLOAT2(0, 0);
};

using EventArgument = std::variant<float, std::string, DirectX::XMFLOAT2, SpawnNPCArgument>;

class IEvent
{
public:
	IEvent() : m_hasStarted(false), m_isComplete(false) {}
	virtual ~IEvent() {};
	virtual void OnStart(EventArgument arg) = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnComplete() = 0;
	virtual void Reset()
	{
		m_hasStarted = false;
		m_isComplete = false;
	}
	virtual bool HasStarted() const { return m_hasStarted; }
	virtual bool IsComplete() const { return m_isComplete; }

protected:
	bool m_hasStarted;
	bool m_isComplete;
};