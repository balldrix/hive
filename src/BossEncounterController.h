#pragma once

class Camera;
class CutsceneManager;
class CombatZoneManager;
class EventManager;
class NPCManager;
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
		NPCManager* npcManager,
		Player* player,
		GameStateManager* gameStateManager,
		EventManager* eventManager
	);
	void Update(float deltaTime);

	void FocusCamera();
	void StartEncounter();
	bool HasFinishedFocus();

private:
	BossEncounterPhase m_currentPhase;
	Camera* m_camera;
	CutsceneManager* m_cutsceneManager;
	CombatZoneManager* m_combatZoneManager;
	NPCManager* m_npcManager;
	Player* m_player;
	GameStateManager* m_gameStateManager;
	EventManager* m_eventManager;
};