#pragma once

#include "GameObject.h"

class Animator;
class Spritesheet;

class TravelPrompt : public GameObject
{
public:
	TravelPrompt();
	~TravelPrompt();

	void Init(Graphics* graphics);
	void Render(Graphics* graphics);
	void Update(float deltaTime);
	void DeleteAll();

private:
	Animator* m_animator;
	Spritesheet* m_spritesheet;
};