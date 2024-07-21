#pragma once

#include "pch.h"
#include "GameState.h"
#include "AABB.h"
#include "TilemapData.h"
#include "ParticleSystem.h"

class GameStateManager;
class Graphics;
class Input;
class Camera;
class ControlSystem;
class QuadMesh;
class Texture;
class Spritesheet;
class Sprite;
class Animator;
class Player;
class HitBoxManager;
class NPCManager;
class InGameHudManager;
template<class T> class StateMachine;
class EncounterHandler;
class TravellingHandler;
class GameOverScreenController;
class SoundSource;
class LevelRenderer;
class ImpactFx;
class Shader;

class GameplayGameState : public GameState
{
public:
	GameplayGameState();
	GameplayGameState(GameStateManager* gameStateManager);
	virtual ~GameplayGameState();

	void CheckForEncounter();
	void Tick(float deltaTime);
	float GetDeltaTime() const { return m_deltaTime; }

	void OnEntry();
	void OnExit();

	void ProcessInput();
	void Update(float deltaTime);
	void ProcessCollisions();
	void SpawnParticles(const Vector2& position, const Vector2& velocity, Color startColour, Color endColour, float lifeTime, unsigned int number);
	void Render();

	void ReleaseAll();
	void ResetGame();

	void SetPlayerBoundaryX(float minX, float maxX);
	void ToggleHitBoxes();

	Camera* GetCamera() const { return m_camera; }
	Player* GetPlayer() const { return m_player; }
	InGameHudManager* GetHudManager() const { return m_hudManager; }
	TravellingHandler* GetTravellingHandler() const { return m_travellingHandler; }
	NPCManager* GetNPCManager() const { return m_NPCManager; }
	EncounterHandler* GetEncounterHandler() const { return m_encounterHandler; }
	StateMachine<GameplayGameState>* GetSceneStateMachine() const { return m_sceneStateMachine; }
	Sprite* GetBackground() const { return m_backgroundSprite; }
	GameOverScreenController* GetGameOverScreenController() const { return m_gameOverScreenController; }

private:
	void LoadAssets();
	void DeleteAssets();

	GameStateManager* m_gameStateManager;
	Graphics* m_graphics;
	Input* m_input;

	Camera* m_camera;
	ControlSystem* m_controlSystem;

	QuadMesh* m_quadMesh;
	Shader* m_pointLightShader;

	Texture* m_playerTexture;
	Texture* m_hitBoxTexture;
	Texture* m_standardShadowTexture;
	Texture* m_backgroundTexture;

	Spritesheet* m_playerSprite;
	Sprite* m_playerShadowSprite;
	Sprite* m_hitBoxSprite;
	Sprite* m_backgroundSprite;

	Animator* m_playerAnimator;

	HitBoxManager* m_playerHitBoxManager;

	NPCManager* m_NPCManager;

	Player* m_player;

	InGameHudManager* m_hudManager;
	StateMachine<GameplayGameState>* m_sceneStateMachine;
	EncounterHandler* m_encounterHandler;
	TravellingHandler* m_travellingHandler;
	LevelRenderer* m_levelRenderer;

	GameOverScreenController* m_gameOverScreenController;

	SoundSource* m_musicSoundSource;

	bool m_canAttack;
	bool m_running;

	AABB m_playerBoundary;

	float m_deltaTime;
	float m_stopTimer;
	bool m_displayHitBoxes;

	Texture* m_impactFxTexture;
	Spritesheet* m_impactFxSpritesheet;
	Animator* m_impactFxAnimator;
	ImpactFx* m_impactFx;
	ParticleSystem* m_particleSystem;
	ParticleData m_particleData;
};