#pragma once

#include "EnemyDefinition.h"

#include <string>

class Camera;
class CutsceneManager;
class Enemy;
class EventManager;
class Graphics;
class Player;
class Sprite;
class Spritesheet;
class ProjectileManager;

class NPCFactory
{
public:
	NPCFactory();
	~NPCFactory() {};

	void Init(Camera* camera, Player* player, CutsceneManager* cutsceneManager, EventManager* eventManager, ProjectileManager* projectileManager);
	
	Enemy* GetEnemy(const std::string& id, EnemyDefinition definition);

private:
	Enemy* CreateNormalEnemy(const std::string& id, EnemyDefinition& definition);
	Enemy* CreateFallingEnemy(const std::string& id, EnemyDefinition& definition);
	Enemy* CreateRangedEnemy(const std::string& id, EnemyDefinition& definition, ProjectileManager* projectileManager);

	Camera* m_camera;
	Player* m_player;
	CutsceneManager* m_cutsceneManager;
	EventManager* m_eventManager;
	ProjectileManager* m_projectileManager;
};