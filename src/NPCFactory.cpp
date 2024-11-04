#include "NPCFactory.h"

#include "AssetLoader.h"
#include "Enemy.h"
#include "EnemyData.h"
#include "EnemyIdleState.h"
#include "EnemyRunningState.h"
#include "Graphics.h"
#include "HitBoxManager.h"
#include "KingMook.h"
#include "KingMookEnemyGlobalState.h"
#include "MookEnemyGlobalState.h"
#include "MookRunningEnemyGlobalState.h"
#include "Player.h"
#include "RunningEnemy.h"

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
	if(data.type == "mook")
		return CreateMook(data);

	if (data.type == "mook_runner")
		return CreateMookRunner(data);

	if(data.type == "boss")
		return CreateBoss(data);

	return nullptr;
}

Enemy* NPCFactory::CreateMook(EnemyData& data)
{
	auto mook = new Enemy();
	mook->Init(m_graphics, m_camera, m_player, data,
				AssetLoader::GetTexture("t_shadow"),
				MookEnemyGlobalState::Instance(),
				EnemyIdleState::Instance());

	return mook;
}

Enemy* NPCFactory::CreateMookRunner(EnemyData& data)
{
	auto mook = new RunningEnemy();
	mook->Init(m_graphics, m_camera, m_player, data,
				AssetLoader::GetTexture("t_shadow"),
				MookRunningEnemyGlobalState::Instance(),
				EnemyRunningState::Instance());

	return mook;
}

Enemy* NPCFactory::CreateBoss(EnemyData& data)
{
	auto boss = new KingMook();
	boss->Init(m_graphics, m_camera, m_player, data,
				AssetLoader::GetTexture("t_shadow"),
				KingMookEnemyGlobalState::Instance(),
				EnemyIdleState::Instance());

	return boss;
}