#pragma once

#include "EnemyDefinition.h"

class Camera;
class Enemy;
class Graphics;
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
	
	Enemy* GetEnemy(EnemyDefinition definition);

private:
	Enemy* CreateNormalEnemy(EnemyDefinition& definition);
	Enemy* CreateFallingEnemy(EnemyDefinition& definition);

	Graphics* m_graphics;
	Camera* m_camera;
	Player* m_player;
};