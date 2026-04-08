#include "FocusCameraEvent.h"

#include "BossEncounterController.h"
#include "IEvent.h"

FocusCameraEvent::FocusCameraEvent(BossEncounterController* bossEncounterController) :
	IEvent(),
	m_bossEncounterController(bossEncounterController)
{
}

FocusCameraEvent::~FocusCameraEvent()
{
}

void FocusCameraEvent::OnStart(EventArgument arg)
{
	m_bossEncounterController->FocusCamera();
	m_hasStarted = true;
	m_isComplete = false;
}

void FocusCameraEvent::OnUpdate(float deltaTime)
{
	m_isComplete = m_bossEncounterController->HasFinishedFocus();
}
