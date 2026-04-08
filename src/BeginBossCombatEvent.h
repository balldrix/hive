#pragma once

#include "IEvent.h"

class BossEncounterController;

class BeginBossCombatEvent : public IEvent
{
public:
	BeginBossCombatEvent(BossEncounterController* bossEncounterController);
	~BeginBossCombatEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;

private:
	BossEncounterController* m_bossEncounterController;
};
