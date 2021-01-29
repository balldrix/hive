// GameOverScreenController.h
// Christopher Ball 2019-2021

#pragma once

class Graphics;
class Animator;
class GameOverScreen;

class GameOverScreenController
{
public:
	GameOverScreenController();
	~GameOverScreenController();

	void Init(Graphics* graphics);
	void Update(float deltaTime);
	void Render(Graphics* graphics);
	void ReleaseAll();
	void Reset();

private:
	void DeleteAll();

	Animator* m_animator;
	GameOverScreen* m_playerWonScreen;
	GameOverScreen* m_playerLostScreen;
};