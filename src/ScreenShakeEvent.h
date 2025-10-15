#pragma once

#include "IEvent.h"

class ScreenShake;

class ScreenShakeEvent : public IEvent
{
public:
	ScreenShakeEvent(ScreenShake* screenShake);
	~ScreenShakeEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;

private:
	ScreenShake* m_screenShake;
};
