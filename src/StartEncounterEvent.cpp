#include "StartEncounterEvent.h"

#include "BossEncounterController.h"
#include "IEvent.h"

StartEncounterEvent::StartEncounterEvent(BossEncounterController* bossEncounterController) :
	IEvent(),
	m_bossEncounterController(bossEncounterController)
{
}

StartEncounterEvent::~StartEncounterEvent()
{
}

void StartEncounterEvent::OnStart(EventArgument arg)
{
	m_bossEncounterController->StartEncounter();
	m_hasStarted = true;
	m_isComplete = true;
}

void StartEncounterEvent::OnUpdate(float deltaTime)
{
}
