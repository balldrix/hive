#pragma once

#include "pch.h"
#include "Animation.h"

class Spritesheet;

class Animator
{
public:
	Animator();
	~Animator();
	
	void Init(const std::string &fileName, Spritesheet* spriteSheet); // init animator
	void Update(float deltaTime);				// update animation sourceRect

	void SetAnimation(unsigned int index);		// set current animation to play using index
	void SetAnimation(const std::string &name);	// set current animation to play using string

	Animation* GetAnimation() const { return m_currentAnimation; }	// return pointer to current animation playing
	int GetCurrentFrame() const { return m_currentFrame; }			// return current sourceRect in animation

	void AddSoundSource() { m_paused = false; }	// play animation
	void Pause() { m_paused = true; }			// pause animation
	bool IsPaused() const { return m_paused; }	// check if paused
	bool IsDone() const { return m_animDone; }	//

	void Reset();								// reset animation

private:
	Animation* m_currentAnimation;				// pointer to current animation to play
	std::vector<Animation>	m_animationList;	// list of animations to play

	Spritesheet* m_spriteSheet;						// spritesheet data
	bool m_paused;									// is animation paused
	unsigned int m_currentFrame;					// current animation sourceRect to draw
	bool m_animDone;								// has non looping anination finished
	float m_animationTimer;							// timer
};