/*
	Running.h

	Defines "Running" game state.
	Running state is used for the main gameplay state

	Christopher Ball
	Copyright (c) 2015
*/

#ifndef _RUNNING_H_
#define _RUNNING_H_

#include "pch.h"
#include "Timer.h"
#include "GameStateManager.h"
#include "GameState.h"
#include "Constants.h"
#include "Player.h"
#include "Enemy.h"
#include "Randomiser.h"

// forward declarations



//////////////////////////////////////////
// Constants
//////////////////////////////////////////

// start positions
const int				START_POSITION_X			= GlobalConstants::GAME_WIDTH / 2;
const int				START_POSITION_Y			= GlobalConstants::GAME_HEIGHT / 2;

// delay between spawning enemy
const float				ENEMY_SPAWN_DELAY = 0.2f;

//////////////////////////////////////////

class Running : public GameState
{
public:
	Running(GameStateManager* gm);
	~Running();

	void				OnEntry();
	void				OnExit();
	void				CheckInput();
	void				Update(float deltaTime);
	void				Render();
	void				ResetAll();

	void				NewGame();
	void				SpawnEnemy();
	void				CheckCollisions();
	void				AddScore(unsigned int score);

	// toggle the rendering of object hit boxes
	void				SetRenderHitBoxes();

private:

	GameStateManager*	m_pGM;
	Graphics*			m_pGraphics;
	Input*				m_pInput;
	Timer				m_timer;
	
	Player				m_player;
	Enemy				m_enemy[MAX_ENEMY];

	Texture		m_enemyTexture;
	Texture		m_bulletTexture;
	Texture		m_playerTexture;

	void				LoadAssets();
	void				DeleteAssets();

	bool				m_initialised;
	bool				m_isPaused;
	bool				m_showHitBoxes;

	float				m_keyDownDelay;

	// current player score
	unsigned int		m_score;

	// current level
	unsigned int		m_level;
};

#endif _RUNNING_H_