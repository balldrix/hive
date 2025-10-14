#include "NPCFactory.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "CutsceneManager.h"
#include "Enemy.h"
#include "EnemyDefinition.h"
#include "EnemyFallingState.h"
#include "EnemyIdleState.h"
#include "Logger.h"
#include "NormalEnemyGlobalState.h"
#include "NPCManager.h"
#include "Player.h"

#include <fmt/core.h>
#include <string>

NPCFactory::NPCFactory() :
	m_camera(nullptr),
	m_player(nullptr),
	m_cutsceneManager(nullptr),
	m_eventManager(nullptr)
{
}

void NPCFactory::Init(Camera* camera, Player* player, CutsceneManager* cutsceneManager, EventManager* eventManager)
{
	m_camera = camera;
	m_player = player;
	m_cutsceneManager = cutsceneManager;
	m_eventManager = eventManager;
}

Enemy* NPCFactory::GetEnemy(const std::string& id, EnemyDefinition definition)
{
	if (definition.enemyType == EnemyType::Normal)
		return CreateNormalEnemy(id, definition);

	if (definition.enemyType == EnemyType::Falling)
		return CreateFallingEnemy(id, definition);

	Logger::LogWarning(fmt::format("[NPCFactory] No Enemy type {0} found.", EnemyTypeToString(definition.enemyType)));
	return nullptr;
}

Enemy* NPCFactory::CreateNormalEnemy(const std::string& id, EnemyDefinition& definition)
{
	auto mook = new Enemy();
	mook->Init(id, m_camera, m_player, m_cutsceneManager, m_eventManager,
				definition,
		NPCManager::Instance(),
				AssetLoader::GetTexture(definition.shadowId), NormalEnemyGlobalState::Instance(), EnemyIdleState::Instance());

	return mook;
}

Enemy* NPCFactory::CreateFallingEnemy(const std::string& id, EnemyDefinition& definition)
{
	auto spider = new Enemy();
	spider->Init(id, m_camera, m_player, m_cutsceneManager, m_eventManager,
				definition,
		NPCManager::Instance(),
				AssetLoader::GetTexture(definition.shadowId), NormalEnemyGlobalState::Instance(), EnemyFallingState::Instance());

	return spider;
}