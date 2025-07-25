#define NOMINMAX

#include "SoundSource.h"

#include "AudioEngine.h"
#include "GameObject.h"
#include "Logger.h"
#include "Sound.h"

#include <AL/al.h>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <utility>

SoundSource::SoundSource()
{
	Reset();
}

SoundSource::SoundSource(Sound* sound)
{
	Reset();
	Play(sound);
}

void SoundSource::Reset()
{
	m_priority = SoundPriority::Low;
	m_position = Vector3::Zero;
	m_volume = 1.0f;
	m_radius = 120.0f;
	m_timeLeft = 0.0f;
	m_isLooping = false;
	m_currentSource = nullptr;
	m_sound = nullptr;
	m_pitch = 1.0f;
	m_isRelative = false;
	m_offset = 0;
	m_target = nullptr;
}

SoundSource::~SoundSource()
{
	Stop();
}

void SoundSource::Play(OALSource* source)
{
	m_currentSource = source;

	if(!m_currentSource) return;

	m_currentSource->inUse = true;

	alSourcef(m_currentSource->source, AL_MAX_DISTANCE, m_radius);
	alSourcef(m_currentSource->source, AL_REFERENCE_DISTANCE, m_radius * 0.2f);
	alSourcei(m_currentSource->source, AL_BUFFER, m_sound->GetBuffer());
	alSourcei(m_currentSource->source, AL_SEC_OFFSET,
		(int)(m_sound->GetLength() / 1000.0f) - (int)(m_timeLeft / 1000.0f));
	alSourcePlay(m_currentSource->source);
}

void SoundSource::Stop()
{
	if(!m_currentSource) return;

	alSourcef(m_currentSource->source, AL_GAIN, 0.0f);
	alSourceStop(m_currentSource->source);
	alSourcei(m_currentSource->source, AL_BUFFER, 0);

	m_currentSource->inUse = false;
	m_currentSource = nullptr;
}

void SoundSource::Pause()
{
	if (!m_currentSource) return;

	alGetSourcei(m_currentSource->source, AL_SAMPLE_OFFSET, &m_offset);
	alSourcePause(m_currentSource->source);
}

void SoundSource::Resume()
{
	if (!m_currentSource || !m_currentSource->inUse) return;

	alSourcei(m_currentSource->source, AL_SAMPLE_OFFSET, m_offset);
	alSourcePlay(m_currentSource->source);
}

bool SoundSource::CompareNodesByPriority(SoundSource* a, SoundSource* b)
{
	return a->m_priority > b->m_priority;
}

void SoundSource::Update(float deltaTime)
{
	if(m_sound == nullptr)
		return;

	m_timeLeft -= deltaTime;

	while(m_isLooping && m_timeLeft < 0.0f)
		m_timeLeft += m_sound->GetLength();

	if(m_currentSource == nullptr)
		return;

	Vector3 listenerPosition = AudioEngine::Instance()->GetListenerPosition();

	if(m_target != nullptr)
		m_position = Vector3(m_target->GetPositionX(), m_target->GetPositionY() - m_target->GetGroundPosition().y, m_target->GetPositionY());

	Vector3 relativePosition = (m_position - listenerPosition) * 1.6f;

	alSourcef(m_currentSource->source, AL_GAIN, m_volume);
	alSourcei(m_currentSource->source, AL_LOOPING, m_isLooping);
	alSourcef(m_currentSource->source, AL_MAX_DISTANCE, m_radius);
	alSourcef(m_currentSource->source, AL_REFERENCE_DISTANCE, m_radius * 0.2f);
	alSourcef(m_currentSource->source, AL_PITCH, m_pitch);

	alSourcei(m_currentSource->source, AL_SOURCE_RELATIVE, m_isRelative);

	if(m_isRelative) {
		// Play as a UI sound�anchor to listener
		alSource3f(m_currentSource->source, AL_POSITION, 0.0f, 0.0f, 0.0f);
	}
	else {
		// Spatialized sound�use world space
		alSourcefv(m_currentSource->source, AL_POSITION, (float*)&relativePosition);
	}

}

void SoundSource::Play(Sound* sound)
{
	Logger::LogInfo(fmt::format("Playing Sound {}", sound->GetFilename()));

	m_sound = sound;
	Stop();

	if(sound != nullptr)
		m_timeLeft = sound->GetLength();
}

void SoundSource::SetVolume(float volume)
{
	m_volume = std::min(1.0f, std::max(0.0f, volume));
}

void SoundSource::SetPriority(SoundPriority priority) 
{ 
	m_priority = priority; 
}

void SoundSource::SetLooping(bool state) 
{ 
	m_isLooping = state; 
}

void SoundSource::SetRadius(float value) 
{ 
	m_radius = std::max(0.0f, value); 
}

void SoundSource::SetTarget(GameObject* target) 
{
	m_target = target; 
}

void SoundSource::SetPitch(float value) 
{ 
	m_pitch = value; 
}

void SoundSource::SetRelative(bool value) 
{ 
	m_isRelative = value; 
}