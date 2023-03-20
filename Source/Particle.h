#pragma once

#include "pch.h"

class Spritesheet;
class Animator;
class Graphics;

class Particle
{
public:
	Particle();
	~Particle();

	void Init(Spritesheet* spritesheet, Animator* animator);
	void Render(Graphics* graphics);
	void Update(float deltaTime);

	void Emit(const Vector2& position);

private:

	Spritesheet* m_spritesheet;
	Animator* m_animator;
	Vector2 m_position;

	bool m_isActive;
};