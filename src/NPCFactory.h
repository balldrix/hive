#pragma once

#include "EnemyData.h"

class Camera;
class Enemy;
class Graphics;
class InGameHudManager;
class Player;
class Sprite;
class Spritesheet;

class NPCFactory
{
public:
	NPCFactory();
	~NPCFactory() {};

	void Init(Graphics* graphics, 
			  Camera* camera, 
			  Player* player);
	
	Enemy* GetEnemy(EnemyData data);

private:
	Enemy* CreateWasteDog(EnemyData& data);
	Enemy* CreateMook(EnemyData& data);
	Enemy* CreateMookRunner(EnemyData& data);
	Enemy* CreateBoss(EnemyData& data);

	Graphics* m_graphics;
	Camera* m_camera;
	Player* m_player;
};