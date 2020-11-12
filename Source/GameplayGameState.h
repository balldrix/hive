// GameplayGameState.h
// Christopher Ball 2019-2020
// the game state for the main gameplay state

#ifndef _GAMEPLAYGAMESTATE_H_
#define _GAMEPLAYGAMESTATE_H_

#include "pch.h"
#include "GameState.h"

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
class InGameHudManager;
template<class T> class StateMachine;
class EncounterHandler;
class TravellingHandler;

class GameplayGameState : public GameState
{
public:
	GameplayGameState();
	GameplayGameState(GameStateManager* gameStateManager);
	virtual				~GameplayGameState();

	void				CheckForEncounter();
	void				Tick(float deltaTime);
	float				GetDeltaTime() const { return m_deltaTime; }

	void				OnEntry();					
	void				OnExit();					
	
	void				ProcessInput();				
	void				Update(float deltaTime);	
	void				ProcessCollisions();		
	void				Render();					

	void				ReleaseAll();
	void				ResetGame();			

	Camera*				GetCamera() const { return m_camera; }
	Player*				GetPlayer() const { return m_player; }
	InGameHudManager*	GetHudManager() const { return m_hudManager; }
	TravellingHandler*  GetTravellingHandler() const { return m_travellingHandler; }

private:			
	void				LoadAssets();				
	void				DeleteAssets();				

	GameStateManager*	m_gameStateManager;			
	Graphics*			m_graphics;					
	Input*				m_input;					
	
	Camera*				m_camera;					
	ControlSystem*		m_controlSystem;			

	Texture*			m_playerTexture;			
	Texture*			m_enemyTexture;
	Texture*			m_mookPortraitTexture;
	Texture*			m_hitBoxTexture;			
	Texture*			m_shadowTexture;			
	Texture*			m_backgroundTexture;		

	SpriteSheet*		m_playerSprite;				
	Sprite*				m_playerShadowSprite;		
	SpriteSheet*		m_enemySprite;				
	Sprite*				m_mookPortraitSprite;
	Sprite*				m_enemyShadowSprite;		
	Sprite*				m_hitBoxSprite;				
	Sprite*				m_backgroundSprite;			
	
	Animator*			m_playerAnimator;			
	Animator*			m_enemyAnimator;			

	HitBoxManager*		m_playerHitBoxManager;		
	HitBoxManager*		m_enemyHitBoxManager;		

	NPCManager*			m_NPCManager;				

	Player*				m_player;					
	Background*			m_background;				
	
	InGameHudManager*	m_hudManager;
	StateMachine<GameplayGameState>* m_sceneStateMachine;
	EncounterHandler*   m_encounterHandler;
	TravellingHandler*	m_travellingHandler;

	bool				m_canAttack;				
	bool				m_running;					

	unsigned int		m_worldWidth;
	unsigned int		m_worldHeight;

	float				m_deltaTime;
};

#endif _GAMEPLAYGAMESTATE_H_