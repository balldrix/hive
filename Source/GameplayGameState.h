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
class Texture;
class SpriteSheet;
class Sprite;
class Animator;
class Player;
class Dummy;
class ControlSystem;
class HitBoxManager;

const float AttackCoolDown = 0.2f;

class GameplayGameState : public GameState
{
public:
	GameplayGameState();
	GameplayGameState(GameStateManager* gameStateManager);
	virtual ~GameplayGameState();

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
	
	ControlSystem*		m_controlSystem;			// player input control system

	Texture*			m_playerTexture;			// player sprite sheet
	Texture*			m_dummyTexture;				// dummy enemy texture
	Texture*			m_hitBoxTexture;			// basic hitbox texture

	SpriteSheet*		m_playerSprite;				// player sprite object
	SpriteSheet*		m_dummySprite;				// dummy sprite sheet
	Sprite*				m_hitBoxSprite;				// basic hitbox sprite
	
	Animator*			m_playerAnimator;			// class to run player animations
	Animator*			m_dummyAnimator;			// dummy animator class

	HitBoxManager*		m_playerHitBoxManager;		// player hitboxes
	HitBoxManager*		m_dummyHitBoxManager;		// dummy hitboxes

	Player*				m_player;					// pointer to player class
	Dummy*				m_dummy;					// pointer to dummy class

	bool				m_canAttack;				// flag for attack cooldown
	bool				m_running;					// is game running or not
};

#endif _GAMEPLAYGAMESTATE_H_