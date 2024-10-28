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

class GameplayGameState : public GameState
{
public:
	GameplayGameState();
	GameplayGameState(GameStateManager* gameStateManager);
	virtual ~GameplayGameState();

	void CheckForEncounter();
	float GetDeltaTime() const { return m_deltaTime; }

	void OnEntry() override;
	void OnExit() override;

	void LoadAssets() override;
	void DeleteAssets() override;
	void ProcessInput() override;
	void Update(float deltaTime) override;
	void ProcessCollisions() override;
	void Render() override;

	void ReleaseAll() override;

	void SetPlayerBoundaryX(float minX, float maxX);
	void ToggleHitBoxes();

	Camera* GetCamera() const { return m_camera; }
	Player* GetPlayer() const { return m_player; }
	InGameHudManager* GetHudManager() const { return m_hudManager; }
	TravellingHandler* GetTravellingHandler() const { return m_travellingHandler; }
	NPCManager* GetNPCManager() const { return m_NPCManager; }
	EncounterHandler* GetEncounterHandler() const { return m_encounterHandler; }
	StateMachine<GameplayGameState>* GetSceneStateMachine() const { return m_sceneStateMachine; }
	GameOverScreenController* GetGameOverScreenController() const { return m_gameOverScreenController; }
	LevelRenderer* GetLevelRenderer() const { return m_levelRenderer; }

private:
	void SpawnParticles(const Vector2& position, const Vector2& velocity, Color startColour, Color endColour, float lifeTime, unsigned int number);
	void Tick(float deltaTime);
	void ResetGame();

	Graphics* m_graphics;
	Input* m_input;

	Camera* m_camera;
	ControlSystem* m_controlSystem;

	Texture* m_playerTexture;
	Texture* m_hitBoxTexture;
	Texture* m_standardShadowTexture;

	Spritesheet* m_playerSprite;
	Sprite* m_playerShadowSprite;
	Sprite* m_hitBoxSprite;

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