#ifndef _GAMESTATEMANAGER_H_
#define _GAMESTATEMANAGER_H_

#include "pch.h"

// forward declarations
class Graphics;
class Input;
class GameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void							Init(Graphics* graphics, Input* input, AudioEngine* audio); // initialise game state manager

	void							AddState(GameState* state);					// add game state to list
	void							SwitchState(const wchar_t* stateName);		// switch game state
	GameState*						GetCurrentState() const;					// return current game state
	const wchar_t*					GetCurrentStateName() const;				// get current state name
	
	void							ProcessInput();								// process input for game state
	void							Update(float deltaTime);					// update game state
	void							Render();									// render game state
	
	void							ReleaseAll();								// release all game state resources

	Graphics*						GetGraphics() const { return m_graphics; }	// return graphics pointer
	Input*							GetInput() const { return m_input; }		// return input pointer
	AudioEngine*					GetAudio() const { return m_audio; }		// return audio pointer

private:
	GameState*						m_currentState;								// pointer to current game state
	std::vector<GameState*>			m_stateList;								// list of game states
		
	Graphics*						m_graphics;									// pointer to graphics class
	Input*							m_input;									// pointer to input clas
	AudioEngine*					m_audio;									// pointer to audio engine
};


#endif _GAMESTATEMANAGER_H_
