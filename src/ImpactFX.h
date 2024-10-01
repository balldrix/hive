#pragma once

#include "pch.h"

class Spritesheet;
class Animator;
class Graphics;

class ImpactFx
{
public:
	ImpactFx();
	~ImpactFx();

	void Init(Spritesheet* spritesheet, Animator* animator);
	void Render(Graphics* graphics);
	void Update(float deltaTime);

	void DisplayFx(const Vector2& position);
	Vector2 Position() const { return m_position; }

private:

	Spritesheet* m_spritesheet;
	Animator* m_animator;
	Vector2 m_position;

	bool m_isActive;
};