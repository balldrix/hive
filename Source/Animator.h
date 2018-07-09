// Animator.h
// Christopher Ball 2018
// Class for animating sprites

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "pch.h"
#include "Animation.h"

class Animator
{
public:
	Animator();
	~Animator();
	void Init(std::string fileName);		// init animator
	void Update(float deltaTime);			// update animation sourceRect

	void SetAnimation(unsigned int index);	// set current animation to play using index
	void SetAnimation(std::string name);	// set current animation to play using string

	Animation* GetAnimation() const { return m_currentAnimation; }	// return pointer to current animation playing
	int GetCurrentFrame() const { return m_currentFrame; }			// return current sourceRect in animation

	void Play() { m_paused = false; }			// play animation
	void Pause() { m_paused = true; }			// pause animation
	bool IsPaused() const { return m_paused; }	// check if paused
	bool IsDone() const { return m_animDone; }	//

	void Reset();								// reset animation

private:
	Animation* m_currentAnimation;				// pointer to current animation to play
	std::vector<Animation>	m_animationList;	// list of animations to play

	bool m_paused;							// is animation paused
	unsigned int m_currentFrame;			// current animation sourceRect to draw
	bool m_animDone;						// has non looping anination finished
	float m_animationTimer;					// timer
};

#endif // !_ANIMATOR_H_
