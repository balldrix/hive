#include "SoundEmitter.h"

#include "AudioEngine.h"

SoundEmitter::SoundEmitter()
{
	Reset();
}

SoundEmitter::SoundEmitter(Sound* sound)
{
	Reset();
	SetSound(sound);
}

void SoundEmitter::Reset()
{
	m_priority = SoundPriority::Low;
	m_volume = 1.0f;
	m_radius = 500.0f;
	m_timeLeft = 0.0f;
	m_isLooping = true;
	m_currentSource = nullptr;
	m_sound = nullptr;
}

SoundEmitter::~SoundEmitter()
{
	DetachSource();
}

void SoundEmitter::AttachSource(OALSource* source)
{
	m_currentSource = source;

	if(!m_currentSource)
		return;

	m_currentSource->inUse = true;

	alSourcef(m_currentSource->source, AL_MAX_DISTANCE, m_radius);
	alSourcef(m_currentSource->source, AL_REFERENCE_DISTANCE, m_radius * 0.2f);
	alSourcei(m_currentSource->source, AL_BUFFER, m_sound->GetBuffer());
	alSourcei(m_currentSource->source, AL_SEC_OFFSET, 
			  (m_sound->GetLength() / 1000.0f) - (m_timeLeft / 1000.0f));
	alSourcePlay(m_currentSource->source);
}

void SoundEmitter::DetachSource()
{
	if(!m_currentSource)
		return;

	alSourcef(m_currentSource->source, AL_GAIN, 0.0f);
	alSourceStop(m_currentSource->source);
	alSourcei(m_currentSource->source, AL_BUFFER, 0);

	m_currentSource->inUse = false;
	m_currentSource = nullptr;
}

bool SoundEmitter::CompareNodesByPriority(SoundEmitter* a, SoundEmitter* b)
{
	return a->m_priority > b->m_priority;
}

void SoundEmitter::Update(float deltaTime)
{
	m_timeLeft -= deltaTime;

	while(m_isLooping && m_timeLeft < 0.0f)
		m_timeLeft += m_sound->GetLength();

	if(m_currentSource == nullptr)
		return;

	Vector3 position;

	if(m_target != nullptr)
		position = Vector3(m_target->GetPositionX(), m_target->GetPositionY() - m_target->GetGroundPosition().y, m_target->GetPositionY());
	else
		position = m_position;

	alSourcefv(m_currentSource->source, AL_POSITION, (float*) &position);
	alSourcef(m_currentSource->source, AL_GAIN, m_volume);
	alSourcei(m_currentSource->source, AL_LOOPING, m_isLooping);
	alSourcef(m_currentSource->source, AL_MAX_DISTANCE, m_radius);
	alSourcef(m_currentSource->source, AL_REFERENCE_DISTANCE, m_radius * 0.2f);
}

void SoundEmitter::SetSound(Sound* sound)
{
	m_sound = sound;
	DetachSource();

	if(sound != nullptr)
		m_timeLeft = sound->GetLength();
}

