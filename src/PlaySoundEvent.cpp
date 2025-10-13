#include "PlaySoundEvent.h"

#include "AssetLoader.h"
#include "IEvent.h"
#include "Logger.h"
#include "Sound.h"
#include "SoundSource.h"

#include <string>
#include <variant>

PlaySoundEvent::PlaySoundEvent(SoundSource* soundSource) : 
	IEvent(),
	m_soundSource(soundSource)
{
}

PlaySoundEvent::~PlaySoundEvent()
{
}

void PlaySoundEvent::OnStart(EventArgument arg)
{
	if(!std::holds_alternative<std::string>(arg))
	{
		Logger::LogError("[PlaySoundEvent] [OnStart] Incorrect argument for PlaySoundEvent, needs string");
		return;
	}

	m_hasStarted = true;

	auto& id = std::get<std::string>(arg);
	Sound* sound = AssetLoader::GetSound(id);

	if(sound == nullptr) return;
	m_soundSource->Play(sound);
}

void PlaySoundEvent::OnUpdate(float deltaTime)
{
	if(m_soundSource->GetTimeLeft() > 0.0f) return;

	m_isComplete = true;
}
