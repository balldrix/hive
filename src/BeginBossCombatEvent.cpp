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
}

void BeginBossCombatEvent::OnUpdate(float deltaTime)
{
}
