// GameplayGameState.h
// Christopher Ball 2019
// the game state for the main gameplay state

#ifndef _GAMEPLAYGAMESTATE_H_
#define _GAMEPLAYGAMESTATE_H_

#include "pch.h"
#include "GameState.h"

// forward declarations
class GameStateManager;
class Graphics;
class Input;
class Camera;
class ControlSystem;
class Texture;
class SpriteSheet;
class Sprite;
class Animator;
class Player;
class Background;
class HitBoxManager;
class NPCManager;

class GameplayGameState : public GameState
{
public:
	GameplayGameState();
	GameplayGameState(GameStateManager* gameStateManager);
	virtual				~GameplayGameState();

	void				OnEntry();					// calls the load assets method
	void				OnExit();					// calls the delete assets method
	
	void				ProcessInput();				// processes input from player
	void				Update(float deltaTime);	// update state
	void				ProcessCollisions();		// check for collisions
	void				Render();					// render state

	void				ReleaseAll();				// release all texture memory
	void				ResetGame();				// reset game and play again

private:			
	void				LoadAssets();				// load game state assets
	void				DeleteAssets();				// delete game state assets

	GameStateManager*	m_gameStateManager;			// game state manager pointer
	Graphics*			m_graphics;					// graphics pointer
	Input*				m_input;					// input class pointer		
	
	Camera*				m_camera;					// camera controller
	ControlSystem*		m_controlSystem;			// player input control 

	Texture*			m_playerTexture;			// player sprite sheet
	Texture*			m_enemyTexture;				// enemy enemy texture
	Texture*			m_hitBoxTexture;			// basic hitbox texture
	Texture*			m_shadowTexture;			// shadow texture
	Texture*			m_backgroundTexture;		// background texture

	SpriteSheet*		m_playerSprite;				// player sprite object
	Sprite*				m_playerShadowSprite;		// player shadow
	SpriteSheet*		m_enemySprite;				// enemy sprite sheet
	Sprite*				m_enemyShadowSprite;		// enemy shadow
	Sprite*				m_hitBoxSprite;				// basic hitbox sprite
	Sprite*				m_backgroundSprite;			// background sprite
	
	Animator*			m_playerAnimator;			// class to run player animations
	Animator*			m_enemyAnimator;			// enemy animator class

	HitBoxManager*		m_playerHitBoxManager;		// player hitboxes
	HitBoxManager*		m_enemyHitBoxManager;		// enemy hitboxes

	NPCManager*			m_NPCManager;				// enemy manager

	Player*				m_player;					// pointer to player class
	Background*			m_background;				// pointer to background object

	bool				m_canAttack;				// flag for attack cooldown
	bool				m_running;					// is game running or not

	// world
	unsigned int		m_worldWidth;
	unsigned int		m_worldHeight;
};

#endif _GAMEPLAYGAMESTATE_H_