#pragma once

#include "AnimatedSpriteData.h"
#include "CutsceneData.h"
#include "EnemyDefinition.h"
#include "HitBoxData.h"

#include <string>
#include <vector>

class GameDataManager
{
public:
	static void Init();
	static void Destroy();
	
	static std::vector<CutsceneData> LoadAllCutscenes(const std::string path);
	static AnimatedSpriteData LoadAnimatedSpriteData(std::string path);
	static std::vector<HitBoxData> LoadHitboxData(std::string path);
	static void LoadAllEnemyDefinitions();
	static EnemyDefinition GetEnemyDefinition(const std::string& id);

private:
	GameDataManager() {};
	~GameDataManager() {};

	static GameDataManager* s_instance;
	std::vector<EnemyDefinition> m_enemyDefinitions;
};