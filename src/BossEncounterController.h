#pragma once

class Enemy;
class Camera;
class CutsceneManager;
class CombatZoneManager;
class EnemySpawnManager;
class EventManager;
class Player;
class GameStateManager;

class BossEncounterController
{
public:
	enum class BossEncounterPhase
	{
		Dormant,
		Intro,
		Combat,
		Victory,
		GameOver,
		Finished
	};

	BossEncounterController();
	~BossEncounterController();

	void Init(
		Camera* camera,
		CutsceneManager* cutsceneManager,
		CombatZoneManager* combatZoneManager,
		EnemySpawnManager* spawnManager,
		Player* player,
		GameStateManager* gameStateManager,
		EventManager* eventManager
	);
	void Update(float deltaTime);

	void FocusCamera();
	void StartEncounter();
	void BeginBossCombat();
	bool HasFinishedFocus();

private:
	Enemy* m_boss;
	BossEncounterPhase m_currentPhase;
	Camera* m_camera;
	CutsceneManager* m_cutsceneManager;
	CombatZoneManager* m_combatZoneManager;
	EnemySpawnManager* m_enemySpawnManager;
	Player* m_player;
	GameStateManager* m_gameStateManager;
	EventManager* m_eventManager;
};
