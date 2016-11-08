#ifndef _CONTROLSCREEN_H_
#define _CONTROLSCREEN_H_

#include "Sprite.h"
#include "GameStateManager.h"

class ControlScreen : public GameState
{
public:
	ControlScreen(GameStateManager* gm);
	~ControlScreen();

	void		OnEntry();
	void		OnExit();

	void		CheckInput(float deltaTime);
	void		Update(float deltaTime);
	void		Render();

private:

	GameStateManager*	m_pGM;
	Graphics*			m_pGraphics;
	Input*				m_input;

	void		LoadAssets();
	void		DeleteAssets();

};

#endif _CONTROLSCREEN_H_