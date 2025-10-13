#pragma once

#include "IEvent.h"

class WaitEvent : public IEvent
{
public:
	WaitEvent();
	~WaitEvent() = default;
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;
	void Reset() override;
private:
	float m_timer;
};