#pragma once

#include "AnimatedSpriteData.h"
#include "EnemyDefinition.h"
#include "HitBoxData.h"

#include <string>
#include <vector>

class GameDataManager
{
public:
	GameDataManager() {};
	~GameDataManager() {};

	static void Init();
	static void Shutdown();
	
	static AnimatedSpriteData LoadAnimatedSpriteData(std::string path);
	static std::vector<HitBoxData> LoadHitboxData(std::string path);
	static void LoadAllEnemyDefinitions();
	static EnemyDefinition GetEnemyDefinition(const std::string& id);

private:
	static GameDataManager* s_instance;
	std::vector<EnemyDefinition> m_enemyDefinitions;
};