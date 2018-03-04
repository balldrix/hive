// Animator.h
// Christopher Ball 2018
// Class for animating sprites

#ifndef _ANIMATOR_H_
#define _ANIMATOR_H_

#include "pch.h"
#include "Animation.h"
#include "SpriteSheet.h"

class Sprite;

class Animator
{
public:
	Animator();
	~Animator();
	void Init(Sprite* spriteSheet,
		SpriteSheet spriteSheetData,
		const wchar_t*); // init animator
	void LoadData(const wchar_t* fileName); // load data from txt file
	void Update(float deltaTime);			// update animation frame

	Animation* GetAnimation() const { return m_currentAnimation; } // return current animation playing
	void SetAnimation(unsigned int index);	// set current animation to play

	void Play() { m_paused = false; }		// play animation
	void Pause() { m_paused = true; }		// pause animation
	bool IsPaused() const { return m_paused; } // check if paused

	void Reset();							// reset animation

private:
	Animation * m_currentAnimation;			// pointer to current animation to play
	std::vector<Animation>	m_animationList; // list of animations to play

	Sprite*	m_spriteSheet;					// sprite sheet
	SpriteSheet m_spriteSheetData;			// sprite sheet data

	bool m_paused;							// is animation paused
	unsigned int m_currentFrame;			// current animation frame to draw
	bool m_animDone;						// has non looping anination finished
	bool m_loop;							// does animation loop
	float m_animationTimer;					// timer
};

#endif // !_ANIMATOR_H_
