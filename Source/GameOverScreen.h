#pragma once

#include <string>

class Graphics;
class Animator;
class Texture;
class Spritesheet;

class GameOverScreen
{
public:
	GameOverScreen();
	~GameOverScreen();

	void Init(Graphics* graphics, Animator* animator, const std::string &texturePath);
	void Update(float deltaTime);
	void Render(Graphics* graphics);
	void Release();
	void Reset();
	void Enable();

private:
	void DeleteAll();

	Animator* m_animator;
	Texture* m_texture;
	Spritesheet* m_spriteSheet;
	bool m_isActive;
};