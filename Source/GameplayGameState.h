#pragma once

#include "pch.h"
#include "GameState.h"
#include "AABB.h"

class GameStateManager;
class Graphics;
class Input;
class Camera;
class ControlSystem;
class Texture;
class Spritesheet;
class Sprite;
class Animator;
class Player;
class Background;
class HitBoxManager;
class NPCManager;
class InGameHudManager;
template<class T> class StateMachine;
class EncounterHandler;
class TravellingHandler;
class GameOverScreenController;
class SoundSource;

class GameplayGameState : public GameState
{
public:
	GameplayGameState();
	GameplayGameState(GameStateManager* gameStateManager);
	virtual								~GameplayGameState();

	void								CheckForEncounter();
	void								Tick(float deltaTime);
	float								GetDeltaTime() const { return m_deltaTime; }

	void								OnEntry();					
	void								OnExit();					
	
	void								ProcessInput();				
	void								Update(float deltaTime);	
	void								ProcessCollisions();		
	void								Render();					

	void								ReleaseAll();
	void								ResetGame();

	void								SetPlayerBoundaryX(float minX, float maxX);

	Camera*								GetCamera() const { return m_camera; }
	Player*								GetPlayer() const { return m_player; }
	InGameHudManager*					GetHudManager() const { return m_hudManager; }
	TravellingHandler*					GetTravellingHandler() const { return m_travellingHandler; }
	NPCManager*							GetNPCManager() const { return m_NPCManager; }
	EncounterHandler*					GetEncounterHandler() const { return m_encounterHandler; }
	StateMachine<GameplayGameState>*	GetSceneStateMachine() const { return m_sceneStateMachine; }
	Sprite*								GetBackground() const { return m_backgroundSprite; }
	GameOverScreenController*			GetGameOverScreenController() const { return m_gameOverScreenController; }

private:			
	void								LoadAssets();				
	void								DeleteAssets();				

	GameStateManager*					m_gameStateManager;			
	Graphics*							m_graphics;					
	Input*								m_input;
	
	Camera*								m_camera;					
	ControlSystem*						m_controlSystem;			

	Texture*							m_playerTexture;		
	Texture*							m_hitBoxTexture;			
	Texture*							m_standardShadowTexture;			
	Texture*							m_largeShadowTexture;			
	Texture*							m_backgroundTexture;		

	Spritesheet*						m_playerSprite;				
	Sprite*								m_standardShadowSprite;	
	Sprite*								m_hitBoxSprite;				
	Sprite*								m_backgroundSprite;			
	
	Animator*							m_playerAnimator;			

	HitBoxManager*						m_playerHitBoxManager;

	NPCManager*							m_NPCManager;				

	Player*								m_player;					
	Background*							m_background;				
	
	InGameHudManager*					m_hudManager;
	StateMachine<GameplayGameState>*	m_sceneStateMachine;
	EncounterHandler*					m_encounterHandler;
	TravellingHandler*					m_travellingHandler;

	GameOverScreenController*			m_gameOverScreenController;

	SoundSource*						m_musicSoundSource;

	bool								m_canAttack;				
	bool								m_running;					

	AABB								m_playerBoundary;

	float								m_deltaTime;
};