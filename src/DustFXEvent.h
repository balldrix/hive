#pragma once

#include "IEvent.h"

class GameObject;

class DustFXEvent : public IEvent
{
public:
	DustFXEvent(GameObject* owner);
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;

private:
	GameObject* m_owner;
};