#pragma once

#include "IEvent.h"

class BossEncounterController;

class StartEncounterEvent : public IEvent
{
public:
	StartEncounterEvent(BossEncounterController* bossEncounterController);
	~StartEncounterEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;

private:
	BossEncounterController* m_bossEncounterController;
};