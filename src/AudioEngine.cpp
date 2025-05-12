#define NOMINMAX

#include "AudioEngine.h"

#include "GameObject.h"
#include "SoundSource.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <algorithm>
#include <directxtk/SimpleMath.h>
#include <exception>
#include <nlohmann/json_fwd.hpp>
#include <utility>
#include <vector>

using namespace DirectX;
using namespace DirectX::DX11;
using namespace SimpleMath;
using json = nlohmann::json;

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

	ALenum error = alGetError();
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

	SetListenerPosition(Vector3(m_listener->GetPositionX(), m_listener->GetPositionY() - m_listener->GetGroundPosition().y, m_listener->GetPositionY()));

	alListenerfv(AL_POSITION, (float*) &m_listenerPosition);

	Vector3 facingDirection = m_listener->GetFacingDirection();
	float orientation[6] = {};
	orientation[0] = facingDirection.x;
	orientation[1] = facingDirection.y;
	orientation[2] = facingDirection.z;
	orientation[3] = 0.0f;
	orientation[4] = 1.0f;
	orientation[5] = 0.0;

	alListenerfv(AL_ORIENTATION, orientation);
}

void AudioEngine::UpdateTemporaryEmitters(float deltaTime)
{
	for(std::vector<SoundSource*>::iterator i = m_frameEmitters.begin(); i != m_frameEmitters.end();)
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

void AudioEngine::RemoveSoundSource(SoundSource* soundEmitter)
{
	for(std::vector<SoundSource*>::iterator i = m_soundEmitters.begin(); i != m_soundEmitters.end();)
	{
		SoundSource* s = *i;
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

	for(std::vector<SoundSource*>::iterator i = m_soundEmitters.begin(); i != m_soundEmitters.end(); ++i)
	{
		m_frameEmitters.push_back((*i));
		(*i)->Update(deltaTime);
	}

	CullTargets();

	if(m_frameEmitters.size() > m_sources.size())
	{
		std::sort(m_frameEmitters.begin(), m_frameEmitters.end(), SoundSource::CompareNodesByPriority);

		StopSources(m_frameEmitters.begin() + (m_sources.size() + 1), m_frameEmitters.end());
		PlaySources(m_frameEmitters.begin(), m_frameEmitters.begin() + m_sources.size());
	}
	else
	{
		PlaySources(m_frameEmitters.begin(), m_frameEmitters.end());
	}

	m_frameEmitters.clear();
}

void AudioEngine::PlaySources(std::vector<SoundSource*>::iterator from, std::vector<SoundSource*>::iterator to)
{
	for(std::vector<SoundSource*>::iterator i = from; i != to; ++i)
	{
		if(!(*i)->GetSource())
		{
			(*i)->Play(GetSource());
		}
	}
}

void AudioEngine::StopSources(std::vector<SoundSource*>::iterator from, std::vector<SoundSource*>::iterator to)
{
	for(std::vector<SoundSource*>::iterator i = from; i != to; ++i)
	{
		(*i)->Stop();
	}
}

void AudioEngine::CullTargets()
{
	for(std::vector<SoundSource*>::iterator i = m_frameEmitters.begin(); i != m_frameEmitters.end();)
	{
		SoundSource* emitter = (*i);
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
			emitter->Stop();
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
