#include "BossEncounterController.h"

#include "BeginBossCombatEvent.h"
#include "Camera.h"
#include "CombatZoneManager.h"
#include "CutsceneManager.h"
#include "Enemy.h"
#include "EventManager.h"
#include "FocusCameraEvent.h"
#include "GameStateManager.h"
#include "GlobalConstants.h"
#include "NPCManager.h"
#include "Player.h"
#include "PlayerIdleState.h"
#include "RestoreCameraEvent.h"
#include "StartEncounterEvent.h"

using namespace GlobalConstants;

BossEncounterController::BossEncounterController() :
	m_camera(nullptr),
	m_cutsceneManager(nullptr),
	m_combatZoneManager(nullptr),
	m_npcManager(nullptr),
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

void BossEncounterController::Init(Camera* camera, CutsceneManager* cutsceneManager, CombatZoneManager* combatZoneManager, NPCManager* npcManager, Player* player, GameStateManager* gameStateManager, EventManager* eventManager)
{
	m_camera = camera;
	m_cutsceneManager = cutsceneManager;
	m_combatZoneManager = combatZoneManager;
	m_npcManager = npcManager;
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
	auto bossPosition = m_npcManager->GetBoss()->GetPositionX();
	auto focusX = bossPosition - (GameWidth * 0.5f);
	m_camera->BeginCutsceneFocus(focusX);
}

void BossEncounterController::StartEncounter()
{
	m_currentPhase = BossEncounterPhase::Intro;
	m_combatZoneManager->ActivateZone("combat_boss");
	m_player->ToggleCameraBounds(false);
	m_player->Stop();
	m_player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
}

bool BossEncounterController::HasFinishedFocus()
{
	return !m_camera->IsCutsceneFocusLocked();
}
