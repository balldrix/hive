#include "RestoreCameraEvent.h"

#include "Camera.h"
#include "IEvent.h"

RestoreCameraEvent::RestoreCameraEvent(Camera* camera) :
	IEvent(),
	m_camera(camera)
{
}

RestoreCameraEvent::~RestoreCameraEvent()
{
}

void RestoreCameraEvent::OnStart(EventArgument arg)
{
	m_camera->ReleaseCutsceneFocus();
	m_hasStarted = true;
	m_isComplete = false;
}

void RestoreCameraEvent::OnUpdate(float deltaTime)
{
	m_isComplete = !m_camera->IsCutsceneFocusReleasing();
}
