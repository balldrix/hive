#pragma once

#include "pch.h"
#include "GameObject.h"
#include <AL/al.h>

class ALCdevice;
class ALCcontext;

class SoundEmitter;

struct OALSource
{
	ALuint source;
	bool inUse;

	OALSource(ALuint src)
	{
		source = src;
		inUse = false;
	}
};

class AudioEngine
{
public:
	static AudioEngine* Instance() { return s_instance; }
	static void Init(unsigned int channels = 32)
	{
		if(s_instance == nullptr)
			s_instance = new AudioEngine(channels);
	}

	static void Destroy() { delete s_instance; }

	void SetListenerPosition(const Vector3& position) { m_listenerPosition = position; }
	void SetMasterVolume(float volume);

	Vector3 GetListenerPosition() { return m_listenerPosition; }

	void AddSoundEmitter(SoundEmitter* soundEmitter) { m_soundEmitters.push_back(soundEmitter); }
	void RemoveSoundEmitter(SoundEmitter* soundEmitter);

	void Update(float deltaTime);

protected:
	AudioEngine(unsigned int channels = 32);
	~AudioEngine();

	void UpdateListener();
	void UpdateTemporaryEmitters(float deltaTime);

	void AttachSources(std::vector<SoundEmitter*>::iterator from, std::vector<SoundEmitter*>::iterator to);
	void DetachSources(std::vector<SoundEmitter*>::iterator from, std::vector<SoundEmitter*>::iterator to);

	void CullTargets();
	OALSource* GetSource();

	Vector3 m_listenerPosition;
	float m_masterVolume;
	ALCdevice* m_alcDevice;
	ALCcontext* m_alcContext;
	GameObject* m_listener;

	std::vector<OALSource*> m_sources;
	std::vector<SoundEmitter*> m_soundEmitters;
	std::vector<SoundEmitter*> m_frameEmitters;

	static AudioEngine* s_instance;
};