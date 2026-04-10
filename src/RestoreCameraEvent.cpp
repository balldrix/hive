#include "RestoreCameraEvent.h"

#include "Camera.h"
#include "IEvent.h"
#include "Logger.h"

#include <variant>

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
	if(!std::holds_alternative<bool>(arg))
	{
		Logger::LogError("[RestoreCameraEvent] [OnStart] Incorrect argument, must be a bool");
		return;
	}

	m_camera->ReleaseCutsceneFocus(std::get<bool>(arg));
	m_hasStarted = true;
	m_isComplete = false;
}

void RestoreCameraEvent::OnUpdate(float deltaTime)
{
	m_isComplete = !m_camera->IsCutsceneFocusReleasing();
}
