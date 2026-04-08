#pragma once

#include "IEvent.h"

class BossEncounterController;

class FocusCameraEvent : public IEvent
{
public:
	FocusCameraEvent(BossEncounterController* bossEncounterController);
	~FocusCameraEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;

private:
	BossEncounterController* m_bossEncounterController;
};