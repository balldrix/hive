#pragma once

#include "AnimatedSpriteData.h"
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
	
	static AnimatedSpriteData LoadAnimatedSpriteData(std::string id);
	static std::vector<HitBoxData> LoadHitboxData(std::string id);

private:
	static GameDataManager* s_instance;
};