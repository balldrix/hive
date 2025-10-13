#pragma once

#include "IEvent.h"

class SoundSource;

class PlaySoundEvent : public IEvent
{
public:
	PlaySoundEvent(SoundSource* soundsource);
	~PlaySoundEvent();
	void OnStart(EventArgument arg) override;
	void OnUpdate(float deltaTime) override;

private:
	SoundSource* m_soundSource;
};