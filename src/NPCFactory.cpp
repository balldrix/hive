#include "NPCFactory.h"

#include "AssetLoader.h"
#include "Enemy.h"
#include "EnemyData.h"
#include "EnemyFallingState.h"
#include "EnemyIdleState.h"
#include "EnemyRunningState.h"
#include "Graphics.h"
#include "HitBoxManager.h"
#include "KingMook.h"
#include "KingMookEnemyGlobalState.h"
#include "Logger.h"
#include "MookEnemyGlobalState.h"
#include "MookRunningEnemyGlobalState.h"
#include "NPCManager.h"
#include "Player.h"
#include "RunningEnemy.h"

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

Enemy* NPCFactory::GetEnemy(EnemyData data)
{
	if(data.type == "jungle-ape")
		return CreateMook(data);

	if(data.type == "waste-dog")
		return CreateWasteDog(data);

	if(data.type == "mook")
		return CreateMook(data);

	if(data.type == "mook_runner")
		return CreateMookRunner(data);

	if(data.type == "boss")
		return CreateBoss(data);

	if(data.type == "waste-lobster")
		return CreateWasteDog(data);

	if(data.type == "lift-spider")
		return CreateSpider(data);

	Logger::LogWarning(fmt::format("[NPCFactory] No Enemy type {0} found.", data.type));
	return nullptr;
}

Enemy* NPCFactory::CreateWasteDog(EnemyData& data)
{
	auto enemy = new Enemy();
	enemy->Init(m_graphics, m_camera, m_player, data,
				NPCManager::Instance(),
				AssetLoader::GetTexture("t_shadow_l"),
				MookEnemyGlobalState::Instance(),
				EnemyIdleState::Instance());

	return enemy;
}

Enemy* NPCFactory::CreateMook(EnemyData& data)
{
	auto mook = new Enemy();
	mook->Init(m_graphics, m_camera, m_player, data,
				NPCManager::Instance(),
				AssetLoader::GetTexture("t_shadow_s"),
				MookEnemyGlobalState::Instance(),
				EnemyIdleState::Instance());

	return mook;
}

Enemy* NPCFactory::CreateMookRunner(EnemyData& data)
{
	auto mook = new RunningEnemy();
	mook->Init(m_graphics, m_camera, m_player, data,
				NPCManager::Instance(),
				AssetLoader::GetTexture("t_shadow_s"),
				MookRunningEnemyGlobalState::Instance(),
				EnemyRunningState::Instance());

	return mook;
}

Enemy* NPCFactory::CreateBoss(EnemyData& data)
{
	auto boss = new KingMook();
	boss->Init(m_graphics, m_camera, m_player, data,
				NPCManager::Instance(),
				AssetLoader::GetTexture("t_shadow_l"),
				KingMookEnemyGlobalState::Instance(),
				EnemyIdleState::Instance());

	return boss;
}

Enemy* NPCFactory::CreateSpider(EnemyData& data)
{
	auto spider = new Enemy();
	spider->Init(m_graphics, m_camera, m_player, data,
				NPCManager::Instance(),
				AssetLoader::GetTexture("t_shadow_l"),
				MookEnemyGlobalState::Instance(),
				EnemyFallingState::Instance());

	return spider;
}