#pragma once

#include <directxtk/SimpleMath.h>

using namespace DirectX::SimpleMath;

enum class SoundPriority {
	Low = 0,
	Medium,
	High,
	Always
};

struct OALSource;
class GameObject;
class Sound;

class SoundSource {
public:
	SoundSource();
	SoundSource(Sound* sound);
	~SoundSource();

	void Reset();
	void Play(Sound* sound);
	void SetVolume(float volume);
	void SetPriority(SoundPriority priority);
	void SetLooping(bool state);
	void SetRadius(float value);
	void SetTarget(GameObject* target);
	void SetPitch(float value);
	void SetRelative(bool value);

	Sound* GetSound() { return m_sound; }
	SoundPriority GetPriority() const { return m_priority; }
	float GetVolume() const { return m_volume; }
	bool GetLooping() const { return m_isLooping; }
	float GetRadius() const { return m_radius; }
	GameObject* GetTarget() const { return m_target; }
	float GetTimeLeft() const { return m_timeLeft; }
	OALSource* GetSource() { return m_currentSource; }

	void Play(OALSource* source);
	void Stop();
	void Pause();
	void Resume();

	static bool CompareNodesByPriority(SoundSource* a, SoundSource* b);
	virtual void Update(float deltaTime);

protected:
	Sound* m_sound;
	OALSource* m_currentSource;
	SoundPriority m_priority;
	Vector3 m_position;
	float m_volume;
	float m_radius;
	GameObject* m_target;
	bool m_isLooping;
	float m_timeLeft;
	float m_pitch;
	bool m_isRelative;
};