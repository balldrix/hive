#include "AudioEngine.h"

#include "SoundEmitter.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <stdexcept>
#include <algorithm>

AudioEngine* AudioEngine::s_instance = nullptr;

AudioEngine::AudioEngine(unsigned int channels) :
	m_listener(nullptr),
	m_masterVolume(1.0f)
{
	m_alcDevice = alcOpenDevice(nullptr);
	if(m_alcDevice == nullptr)
		throw std::exception();

	m_alcContext = alcCreateContext(m_alcDevice, nullptr);
	if(m_alcContext == nullptr)
		throw std::exception();

	if(!alcMakeContextCurrent(m_alcContext))
		throw std::exception();

	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);

	for(size_t i = 0; i < channels; i++)
	{
		ALuint source;

		alGenSources(1, &source);
		ALenum error = alGetError();

		if(error == AL_NO_ERROR)
			m_sources.push_back(new OALSource(source));
		else
			break;
	}
}

AudioEngine::~AudioEngine()
{
	alcMakeContextCurrent(nullptr);
	
	for(std::vector<OALSource*>::iterator i = m_sources.begin(); i != m_sources.end(); ++i)
	{
		alDeleteSources(1, &(*i)->source);
		delete (*i);
	}

	alcDestroyContext(m_alcContext);
	alcCloseDevice(m_alcDevice);
}

void AudioEngine::SetMasterVolume(float volume)
{
	volume = std::max(0.0f, volume);
	volume = std::min(1.0f, volume);
	m_masterVolume = volume;
	alListenerf(AL_GAIN, m_masterVolume);
}

void AudioEngine::UpdateListener()
{
	if(m_listener == nullptr)
		return;

	alListenerfv(AL_POSITION, (float*) &m_listenerPosition);
	alListenerfv(AL_ORIENTATION, (float*) &Vector3::Up);
}

void AudioEngine::UpdateTemporaryEmitters(float deltaTime)
{
	for(std::vector<SoundEmitter*>::iterator i = m_frameEmitters.begin(); i != m_frameEmitters.end();)
	{
		if((*i)->GetTimeLeft() < 0.0f && !(*i)->GetLooping())
		{
			delete(*i);
			i = m_frameEmitters.erase(i);
		}
		else
		{
			(*i)->Update(deltaTime);
			++i;
		}
	}
}

void AudioEngine::RemoveSoundEmitter(SoundEmitter* soundEmitter)
{
	for(std::vector<SoundEmitter*>::iterator i = m_soundEmitters.begin(); i != m_soundEmitters.end();)
	{
		SoundEmitter* s = *i;
		if(s == soundEmitter)
		{
			m_soundEmitters.erase(i);
			return;
		}
		else
		{
			++i;
		}
	}
}

void AudioEngine::Update(float deltaTime)
{
	UpdateListener();
	UpdateTemporaryEmitters(deltaTime);

	for(std::vector<SoundEmitter*>::iterator i = m_soundEmitters.begin(); i != m_soundEmitters.end(); ++i)
	{
		m_frameEmitters.push_back((*i));
		(*i)->Update(deltaTime);
	}

	CullTargets();

	if(m_frameEmitters.size() > m_sources.size())
	{
		std::sort(m_frameEmitters.begin(), m_frameEmitters.end(), SoundEmitter::CompareNodesByPriority);

		DetachSources(m_frameEmitters.begin() + (m_sources.size() + 1), m_frameEmitters.end());
		AttachSources(m_frameEmitters.begin(), m_frameEmitters.begin() + m_sources.size());
	}
	else
	{
		AttachSources(m_frameEmitters.begin(), m_frameEmitters.end());
	}

	m_frameEmitters.clear();
}

void AudioEngine::AttachSources(std::vector<SoundEmitter*>::iterator from, std::vector<SoundEmitter*>::iterator to)
{
	for(std::vector<SoundEmitter*>::iterator i = from; i != to; ++i)
	{
		if(!(*i)->GetSource())
		{
			(*i)->AttachSource(GetSource());
		}
	}
}

void AudioEngine::DetachSources(std::vector<SoundEmitter*>::iterator from, std::vector<SoundEmitter*>::iterator to)
{
	for(std::vector<SoundEmitter*>::iterator i = from; i != to; ++i)
	{
		(*i)->DetachSource();
	}
}

void AudioEngine::CullTargets()
{
	for(std::vector<SoundEmitter*>::iterator i = m_frameEmitters.begin(); i != m_frameEmitters.end();)
	{
		SoundEmitter* emitter = (*i);
		float distance;

		if(emitter->GetTarget() != nullptr)
		{
			auto target = emitter->GetTarget();
			Vector3 targetLocation = Vector3(target->GetPositionX(), target->GetGroundPosition().y - target->GetPositionY(), target->GetPositionY());
			distance = Vector3::Distance(targetLocation, m_listenerPosition);
		}
		else
		{
			distance = 0.0f;
		}

		if(distance > emitter->GetRadius() || !emitter->GetSound() || emitter->GetTimeLeft() < 0.0f)
		{
			emitter->DetachSource();
			i = m_frameEmitters.erase(i);
		}
		else
		{
			++i;
		}
	}
}

OALSource* AudioEngine::GetSource()
{
	for(std::vector<OALSource*>::iterator i = m_sources.begin(); i != m_sources.end(); ++i)
	{
		OALSource* source = *i;
		if(!source->inUse)
		{
			return source;
		}
	}

	return nullptr;
}
