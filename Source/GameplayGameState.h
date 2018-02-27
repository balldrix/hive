// GameplayGameState.h
// Christopher Ball 2018
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
class Sprite;
class Player;

// constants
const unsigned int PLAYER_START_X = 30;	// game start player position X
const unsigned int PLAYER_START_Y = 70;	// game start player position y

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
	void				Render();					// render state
	void				ReleaseAll();				// release all texture memory

	void				ResetGame();				// reset game and play again
																
private:			
	void				LoadAssets();				// load game state assets
	void				DeleteAssets();				// delete game state assets

	GameStateManager*	m_gameStateManager;			// game state manager pointer
	Graphics*			m_graphics;					// graphics pointer
	Input*				m_input;					// input class pointer		

	Texture*			m_playerTexture;			// player sprite sheet

	Sprite*				m_playerSprite;				// player sprite object

	Player*				m_player;					// pointer to player class

	bool				m_running;					// is game running or not
};

#endif _GAMEPLAYGAMESTATE_H_