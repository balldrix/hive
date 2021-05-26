#pragma once

#include "GameObject.h"
#include "Sound.h"
#include <algorithm>

enum class SoundPriority
{
	Low = 0,
	Medium,
	High,
	Always
};

struct OALSource;

class SoundSource
{
public:
	SoundSource();
	SoundSource(Sound* sound);
	~SoundSource();

	void			Reset();

	void			SetSound(Sound* sound);
	void			SetPriority(SoundPriority priority) { m_priority = priority; }
	void			SetVolume(float volume) { m_volume = std::min(1.0f, std::max(0.0f, volume)); }
	void			SetLooping(bool state) { m_isLooping = state; }
	void			SetRadius(float value) { m_radius = std::max(0.0f, value); }
	void			SetTarget(GameObject* target) { m_target = target; }

	Sound*			GetSound() { return m_sound; }
	SoundPriority	GetPriority() { return m_priority; }
	float			GetVolume() { return m_volume; }
	bool			GetLooping() { return m_isLooping; }
	float			GetRadius() { return m_radius; }
	GameObject*		GetTarget() const { return m_target; }
	float			GetTimeLeft() { return m_timeLeft; }
	OALSource*		GetSource() { return m_currentSource; }
	
	void			AttachSource(OALSource* source);
	void			DetachSource();

	static bool		CompareNodesByPriority(SoundSource* a, SoundSource* b);

	virtual void	Update(float deltaTime);

protected:
	Sound*			m_sound;
	OALSource*		m_currentSource;
	SoundPriority	m_priority;
	Vector3			m_position;
	float			m_volume;
	float			m_radius;
	GameObject*		m_target;
	bool			m_isLooping;
	float			m_timeLeft;
};