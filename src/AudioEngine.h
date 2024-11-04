#pragma once

#include "GameObject.h"
#include "Logger.h"

#include <AL/al.h>
#include <DirectXTK/SimpleMath.h>
#include <vector>

struct ALCdevice;
struct ALCcontext;

class SoundSource;

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

		Logger::LogInfo("Initialised Audio Engine.");
	}

	static void Destroy()
	{
		delete s_instance;
		s_instance = nullptr;
	}

	void SetListener(GameObject* object) { m_listener = object; }
	void SetMasterVolume(float volume);

	Vector3 GetListenerPosition() const { return m_listenerPosition; }

	void AddSoundSource(SoundSource* soundSource) { m_soundEmitters.push_back(soundSource); }
	void RemoveSoundSource(SoundSource* soundSource);

	void Update(float deltaTime);

protected:
	AudioEngine(unsigned int channels = 32);
	~AudioEngine();

	void UpdateListener();
	void UpdateTemporaryEmitters(float deltaTime);

	void SetListenerPosition(const Vector3& position) { m_listenerPosition = position; }

	void AttachSources(std::vector<SoundSource*>::iterator from, std::vector<SoundSource*>::iterator to);
	void DetachSources(std::vector<SoundSource*>::iterator from, std::vector<SoundSource*>::iterator to);

	void CullTargets();
	OALSource* GetSource();

	Vector3 m_listenerPosition;
	float m_masterVolume;
	ALCdevice* m_alcDevice;
	ALCcontext* m_alcContext;
	GameObject* m_listener;

	std::vector<OALSource*> m_sources;
	std::vector<SoundSource*> m_soundEmitters;
	std::vector<SoundSource*> m_frameEmitters;

	static AudioEngine* s_instance;
};