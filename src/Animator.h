#pragma once

#include "AnimatedSpriteData.h"

#include <string>

class Animator
{
public:
	Animator();
	~Animator() {};

	void Init(AnimatedSpriteData animatedSpriteData);
	void Update(float deltaTime);

	void SetAnimation(unsigned int index);
	void SetAnimation(const std::string& name);

	AnimationData GetAnimation() const { return m_currentAnimation; }
	int GetCurrentFrame() const { return m_currentFrame; }

	void AddSoundSource() { m_paused = false; }
	void Pause() { m_paused = true; }
	bool IsPaused() const { return m_paused; }
	bool IsDone() const { return m_animDone; }

	void Reset();

private:
	AnimationData m_currentAnimation;
	AnimatedSpriteData m_animatedSpriteData;

	bool m_paused;
	unsigned int m_currentFrame;
	bool m_animDone;
	float m_animationTimer;
};