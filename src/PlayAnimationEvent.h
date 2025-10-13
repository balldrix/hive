#pragma once

#include "IEvent.h"

class Animator;

class PlayAnimationEvent : public IEvent
{
public:
	PlayAnimationEvent(Animator* animator);
	~PlayAnimationEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;

private:
	Animator* m_animator;
};