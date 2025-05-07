#include "NPCFactory.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "Enemy.h"
#include "EnemyDefinition.h"
#include "EnemyFallingState.h"
#include "EnemyIdleState.h"
#include "Graphics.h"
#include "Logger.h"
#include "NormalEnemyGlobalState.h"
#include "NPCManager.h"
#include "Player.h"

#include <fmt/core.h>

NPCFactory::NPCFactory() :
	m_graphics(nullptr),
	m_camera(nullptr),
	m_player(nullptr)
{
}

void NPCFactory::Init(Graphics* graphics,
	Camera* camera,
	Player* player)
{
	m_graphics = graphics;
	m_camera = camera;
	m_player = player;
}

Enemy* NPCFactory::GetEnemy(EnemyDefinition definition)
{
	if(definition.enemyType == EnemyType::Normal)
		return CreateNormalEnemy(definition);

	if(definition.enemyType == EnemyType::Falling)
		return CreateFallingEnemy(definition);

	Logger::LogWarning(fmt::format("[NPCFactory] No Enemy type {0} found.", EnemyTypeToString(definition.enemyType)));
	return nullptr;
}

Enemy* NPCFactory::CreateNormalEnemy(EnemyDefinition& definition)
{
	auto mook = new Enemy();
	mook->Init(m_graphics, m_camera, m_player, definition,
				NPCManager::Instance(),
				AssetLoader::GetTexture("t_shadow_s"),
				NormalEnemyGlobalState::Instance(),
				EnemyIdleState::Instance());

	return mook;
}

Enemy* NPCFactory::CreateFallingEnemy(EnemyDefinition& definition)
{
	auto spider = new Enemy();
	spider->Init(m_graphics, m_camera, m_player, definition,
				NPCManager::Instance(),
				AssetLoader::GetTexture("t_shadow_l"),
				NormalEnemyGlobalState::Instance(),
				EnemyFallingState::Instance());

	return spider;
}