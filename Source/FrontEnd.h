#ifndef _FRONTEND_H_
#define _FRONTEND_H_

#include "Sprite.h"
#include "GameStateManager.h"

// list of menu states
enum FrontEndMenuState
{
	FRONTEND_MAX_OPTIONS = 0
};

class FrontEnd : public GameState
{
public:

	FrontEnd(GameStateManager* gm);
	~FrontEnd();

	void		OnEntry();
	void		OnExit();
	void		CheckInput(float deltaTime);
	void		Update(float deltaTime);
	void		Render();

	// select next option
	void		SelectNext();

	// select previous option
	void		SelectPrevious();
	
	// store the current menu state
	void		SetState(FrontEndMenuState state);
	
	// return the current menu state
	FrontEndMenuState GetState() const { return m_optionState; }

private:

	void		LoadAssets();
	
	void		DeleteAssets();

	GameStateManager*	m_pGM;
	Graphics*			m_pGraphics;
	Input*				m_pInput;

	// game title logo thing

	// array of menu option sprites
	
	// array of bools to allow the menu
	// options to show when they are selected
	
	FrontEndMenuState m_optionState;
};

#endif _FRONTEND_H_