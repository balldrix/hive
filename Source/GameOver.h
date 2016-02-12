#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "Sprite.h"
#include "GameStateManager.h"

class GameOver : public GameState
{
public:

	enum GameOverOptionState
	{
		GAME_OVER_MAX_OPTIONS = 0
	}m_optionState;

	GameOver(GameStateManager* gm);
	~GameOver();

	void		OnEntry();
	void		OnExit();

	void		CheckInput(float deltaTime);
	void		Update(float deltaTime);
	void		Render();

	void		SelectNext();
	void		SelectPrevious();

	void		SetState(GameOverOptionState state);

	GameOverOptionState GetState() const { return m_optionState; }

private:

	GameStateManager*	m_pGM;
	Graphics*			m_pGraphics;
	Input*				m_pInput;

	void		LoadAssets();
	void		DeleteAssets();

	bool		m_selectState[GAME_OVER_MAX_OPTIONS];
};

#endif _GAMEOVER_H_