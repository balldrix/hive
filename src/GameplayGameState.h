#pragma once

#include "EnemySpawner.h"
#include "GameState.h"
#include "ParticleSystem.h"
#include "Player.h"

#include <directxtk/SimpleMath.h>
#include <vector>

class GameStateManager;
class Graphics;
class Input;
class Camera;
class ControlSystem;
class Spritesheet;
class Sprite;
class Animator;
class HitBoxManager;
class NPCManager;
class InGameHudManager;
class GameOverScreenController;
class SoundSource;
class LevelRenderer;
class ImpactFxPool;
class SpriteFx;
class EnemySpawnManager;

class GameplayGameState : public GameState
{
public:
	GameplayGameState();
	GameplayGameState(GameStateManager* gameStateManager);
	virtual ~GameplayGameState();

	float GetDeltaTime() const { return m_deltaTime; }

	void OnEntry() override;
	void OnExit() override;

	void LoadAssets() override;
	void DeleteAssets() override;
	void ProcessInput() override;
	void Update(float deltaTime) override;
	void ProcessCollisions() override;
	void Render() override;

	void UpdateGameBounds(float minX, float maxX);

	Camera* GetCamera() const { return m_camera; }
	Player* GetPlayer() const { return m_player; }
	NPCManager* GetNPCManager() const { return m_NPCManager; }
	LevelRenderer* GetLevelRenderer() const { return m_levelRenderer; }

private:
	void SpawnParticles(const Vector2& position, const Vector2& velocity, Color startColour, Color endColour, float lifeTime, unsigned int number);
	void Tick(float deltaTime);
	void ResetGame();
	void ToggleHitBoxes();
	void TogglePlayerHud();

	Graphics* m_graphics;
	Input* m_input;

	Camera* m_camera;
	ControlSystem* m_controlSystem;
	NPCManager* m_NPCManager;
	Player* m_player;

	LevelRenderer* m_levelRenderer;
	EnemySpawnManager* m_enemySpawnManager;
	SoundSource* m_musicSoundSource;

	bool m_canAttack;
	bool m_running;

	float m_deltaTime;
	float m_stopTimer;
	float m_collisionCooldown;
	bool m_displayHitBoxes;
	bool m_hidePlayerHud;
	bool m_isCollisionOnCooldown;

	ImpactFxPool* m_impactFxPool;
	std::vector<SpriteFx*> m_activeImpacts;
	ParticleSystem* m_particleSystem;
	ParticleData m_particleData;
};