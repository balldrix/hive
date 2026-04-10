#include "BossEncounterController.h"

#include "Animator.h"
#include "BeginBossCombatEvent.h"
#include "Camera.h"
#include "CombatZone.h"
#include "CombatZoneManager.h"
#include "CutsceneManager.h"
#include "Enemy.h"
#include "EnemySpawner.h"
#include "EnemySpawnManager.h"
#include "EventManager.h"
#include "FocusCameraEvent.h"
#include "GameStateManager.h"
#include "GlobalConstants.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "RestoreCameraEvent.h"
#include "StartEncounterEvent.h"
#include "StateMachine.h"

using namespace GlobalConstants;

BossEncounterController::BossEncounterController() :
	m_boss(nullptr),
	m_camera(nullptr),
	m_cutsceneManager(nullptr),
	m_combatZoneManager(nullptr),
	m_enemySpawnManager(nullptr),
	m_player(nullptr),
	m_gameStateManager(nullptr),
	m_eventManager(nullptr),
	m_currentPhase(BossEncounterPhase::Dormant)
{
}

BossEncounterController::~BossEncounterController()
{
	m_eventManager->UnRegisterAllForTarget("BossEncounter");
}

void BossEncounterController::Init(Camera* camera, CutsceneManager* cutsceneManager, CombatZoneManager* combatZoneManager, EnemySpawnManager* spawnManager, Player* player, GameStateManager* gameStateManager, EventManager* eventManager)
{
	m_camera = camera;
	m_cutsceneManager = cutsceneManager;
	m_combatZoneManager = combatZoneManager;
	m_enemySpawnManager = spawnManager;
	m_player = player;
	m_gameStateManager = gameStateManager;
	m_eventManager = eventManager;
	m_eventManager->RegisterEvent("StartEncounter", "BossEncounter", new StartEncounterEvent(this));
	m_eventManager->RegisterEvent("BeginBossCombat", "BossEncounter", new BeginBossCombatEvent(this));
	m_eventManager->RegisterEvent("FocusCamera", "BossEncounter", new FocusCameraEvent(this));
	m_eventManager->RegisterEvent("RestoreCamera", "BossEncounter", new RestoreCameraEvent(m_camera));
}

void BossEncounterController::Update(float deltaTime)
{
}

void BossEncounterController::FocusCamera()
{
	auto bossPosition = m_boss->GetPositionX();
	auto focusX = bossPosition - (GameWidth * 0.75f);
	auto zone = m_combatZoneManager->GetZoneById("combat_boss");
	auto releaseX = zone->GetPosition().x - (GameWidth * 0.5f);
	m_camera->BeginCutsceneFocus(focusX, releaseX);
}

void BossEncounterController::StartEncounter()
{
	m_boss = m_enemySpawnManager->GetSpawner("spawner_boss_1")->SpawnNow();
	m_currentPhase = BossEncounterPhase::Intro;
	m_player->ToggleCameraBounds(false);
	m_player->Stop();
	m_player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
}

void BossEncounterController::BeginBossCombat()
{
	m_currentPhase = BossEncounterPhase::Combat;
	m_boss->GetAnimator()->SetAnimation("idle");
	m_combatZoneManager->ActivateZone("combat_boss");
}

bool BossEncounterController::HasFinishedFocus()
{
	return !m_camera->IsCutsceneFocusLocked();
}
