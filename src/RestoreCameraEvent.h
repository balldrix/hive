#pragma once

#include "IEvent.h"

class Camera;

class RestoreCameraEvent : public IEvent
{
public:
	RestoreCameraEvent(Camera* camera);
	~RestoreCameraEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;

private:
	Camera* m_camera;
};