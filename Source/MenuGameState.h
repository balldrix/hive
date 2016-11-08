// MenuGameState.h
// Christopher Ball 2016
// menu game state

#ifndef _MENUGAMESTATE_H_
#define _MENUGAMESTATE_H_

#include "pch.h"
#include "GameState.h"

// forward declarations
class GameStateManager;
class Graphics;
class Input;
class Texture;
class Sprite;
class Button;
class Instructions;
class Cursor;			

class MenuGameState : public GameState
{
public:
	MenuGameState();
	MenuGameState(GameStateManager* gameStateManager);
	~MenuGameState();

	void				OnEntry();					// calls the load assets method
	void				OnExit();					// calls the delete assets method
	void				ProcessInput();				// processes input from player
	void				Update(float deltaTime);	// update state
	void				Render();					// render state
	void				ReleaseAll();				// release all texture memory

private:
	void				LoadAssets();				// load game state assets
	void				DeleteAssets();				// delete game state assets
	
	GameStateManager*	m_gameStateManager;			// game state manager pointer
	Graphics*			m_graphics;					// graphics pointer
	Input*				m_input;					// input class pointer
	AudioEngine*		m_audio;					// audio engine pointer
	
	std::unique_ptr<SoundEffectInstance> m_backgroundLoop;	// background loop
	SoundEffect*		m_menuMusic;				// menu music
	SoundEffect*		m_clickSound;				// button click sound

	Texture*			m_backgroundTexture;		// background image
	Texture*			m_playButtonTexture;		// play button texture
	Texture*			m_instuctionsButtonTexture; // instructions button texture
	Texture*			m_quitButtonTexture;		// quit button texture
	Texture*			m_instructionsTexture;		// instructions screen texture
	Texture*			m_cursorTexture;			// custom cursor texture
	
	Sprite*				m_backgroundSprite;			// background sprite
	Sprite*				m_playButtonSprite;			// play button sprite
	Sprite*				m_instructionsButtonSprite;	// instructions button sprite
	Sprite*				m_quitButtonSprite;			// quit button sprite
	Sprite*				m_instructionsSprite;		// instructions screen sprite
	Sprite*				m_cursorSprite;				// custom cursor sprite
		
	Button*				m_playButton;				// play game button
	Button*				m_instructionsButton;		// instructions button
	Button*				m_quitButton;				// quit button
	
	Instructions*		m_instructions;				// instructions screen
	
	Cursor*				m_mouseCursor;				// custom mouse cursor
};

#endif _MENUGAMESTATE_H_