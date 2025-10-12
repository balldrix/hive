#pragma once

#include "IEvent.h"

class NPCManager;

class SpawnNPCEvent : public IEvent
{
public:
	SpawnNPCEvent(NPCManager* npcManager);
	~SpawnNPCEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;
	void OnComplete() override;
private:
	NPCManager* m_npcManager;
};