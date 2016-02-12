/*
	Hive.h
	
	Defines Hive game class, main purpose is to implement the game state manager

	Christopher Ball
	Copyright (c) 2015
*/

#ifndef _Hive_H_
#define _Hive_H_

// tells compiler to only load minimal windows header files
#define WIN32_LEAN_AND_MEAN

#include "Game.h"
#include "FrontEnd.h"
#include "ControlScreen.h"
#include "Running.h"
#include "GameOver.h"
#include "Constants.h"
#include "Controls.h"

class Hive : public Game
{
public:

	Hive();
	virtual	~Hive();

	void		Init(HWND hWindow);
	void		Update(float deltaTime);
	void		Render();
	void		ReleaseAll();
	void		ResetAll();


private:
	GameStateManager*	m_stateManager;
};

#endif	_Hive_H_