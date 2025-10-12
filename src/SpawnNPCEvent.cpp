#include "SpawnNPCEvent.h"

#include "IEvent.h"
#include "Logger.h"
#include "NPCManager.h"

#include <variant>

SpawnNPCEvent::SpawnNPCEvent(NPCManager* npcManager) :
	IEvent(),
	m_npcManager(npcManager)
{
}

SpawnNPCEvent::~SpawnNPCEvent()
{
}

void SpawnNPCEvent::OnStart(EventArgument arg)
{
	if(!std::holds_alternative<SpawnNPCArgument>(arg))
	{
		Logger::LogError("[SpawnNPCEvent] [OnStart] Incorrect argument, must be a SpawnEventArgument");
		return;
	}

	SpawnNPCArgument spawnArgument = std::get<SpawnNPCArgument>(arg);
	m_npcManager->SpawnNPC(spawnArgument);
	m_hasStarted = true;
	m_isComplete = true;
}

void SpawnNPCEvent::OnUpdate(float deltaTime)
{
}

void SpawnNPCEvent::OnComplete()
{
}
