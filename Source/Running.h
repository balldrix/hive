/*
	Running.h

	Defines "Running" game state.
	Running state is used for the main gameplay state

	Christopher Ball
	Copyright (c) 2015
*/

#ifndef _RUNNING_H_
#define _RUNNING_H_

#include <math.h>
#include <time.h>
#include "Timer.h"
#include "GameStateManager.h"
#include "Constants.h"
#include "Player.h"
#include "Enemy.h"
#include "Randomiser.h"


//////////////////////////////////////////
// Constants
//////////////////////////////////////////

// start positions
const int				START_X_POSITION			= GAME_WIDTH / 2;
const int				START_Y_POSITION			= GAME_HEIGHT / 2;

// enemy spawn area
const unsigned int		ENEMY_SPAWN__AREA1_MIN_X	= 0;
const unsigned int		ENEMY_SPAWN__AREA1_MIN_Y	= 0;

const unsigned int		ENEMY_SPAWN__AREA1_MAX_X	= 288;
const unsigned int		ENEMY_SPAWN__AREA1_MAX_Y	= 88;

const unsigned int		ENEMY_SPAWN__AREA2_MIN_X	= 960;
const unsigned int		ENEMY_SPAWN__AREA2_MIN_Y	= 480;

const unsigned int		ENEMY_SPAWN__AREA2_MAX_X	= GAME_WIDTH - TILE_SIZE;
const unsigned int		ENEMY_SPAWN__AREA2_MAX_Y	= GAME_HEIGHT - TILE_SIZE;

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
	
	// set random x and y spawn location
	Vector2D			SetSpawnLocation();

	// toggle the rendering of object hit boxes
	void				SetRenderHitBoxes();

private:

	GameStateManager*	m_pGM;
	Graphics*			m_pGraphics;
	Input*				m_pInput;
	Timer				m_timer;
	
	Player				m_player;
	Enemy				m_enemy[MAX_ENEMY];

	//TextureManager		m_enemyTexture;
	TextureManager		m_bulletTexture;
	TextureManager		m_playerTexture;

	void				LoadAssets();
	void				DeleteAssets();

	bool				m_initialised;
	bool				m_isPaused;
	bool				m_canSpawnEnemy;
	bool				m_showHitBoxes;

	float				m_enemySpawnDelay;
	float				m_keyDownDelay;

	Vector2D			m_enemySpawnPosition;

	// current player score
	unsigned int		m_score;

	// current level
	unsigned int		m_level;
};

#endif _RUNNING_H_