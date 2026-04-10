#include "BeginBossCombatEvent.h"

#include "BossEncounterController.h"
#include "IEvent.h"

BeginBossCombatEvent::BeginBossCombatEvent(BossEncounterController* bossEncounterController) :
	IEvent(),
	m_bossEncounterController(bossEncounterController)
{
}

BeginBossCombatEvent::~BeginBossCombatEvent()
{
}

void BeginBossCombatEvent::OnStart(EventArgument arg)
{
	m_bossEncounterController->BeginBossCombat();
	m_hasStarted = true;
	m_isComplete = true;
}

void BeginBossCombatEvent::OnUpdate(float deltaTime)
{
}
