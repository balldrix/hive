#pragma once

#include "GameObject.h"

class Animator;
class Texture;
class Spritesheet;

class TravelPrompt : public GameObject
{
public:
	TravelPrompt();
	~TravelPrompt();

	void Init(Graphics* graphics);
	void Render(Graphics* graphics);
	void Update(float deltaTime);
	void Reset();
	void Release();
	void DeleteAll();

private:
	Animator* m_animator;
	Texture* m_texture;
	Spritesheet* m_spritesheet;
};