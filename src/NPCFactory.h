#pragma once

#include "EnemyData.h"
#include <string>

class Camera;
class Enemy;
class Graphics;
class InGameHudManager;
class Player;
class Sprite;
class Spritesheet;
class Texture;

class NPCFactory
{
public:
	NPCFactory();
	~NPCFactory();
	void Init(Graphics* graphics, 
			  Camera* camera, 
			  Player* player, 
			  InGameHudManager* hudManager,
			  Texture* standardShadowTexture,
			  Texture* hitBoxTexture);
	
	Enemy* GetEnemy(EnemyData data);

private:
	Enemy* CreateMook(EnemyData& data);
	Enemy* CreateMookRunner(EnemyData& data);
	Enemy* CreateBoss(EnemyData& data);
	void DeleteAll();
	void ReleaseAll();

	Graphics* m_graphics;
	Camera* m_camera;
	Player* m_player;
	InGameHudManager* m_hudManager;
	Texture* m_mookTexture;
	Texture* m_kingMookTexture;
	Texture* m_standardShadowTexture;
	Texture* m_mookPortraitTexture;
	Texture* m_kingMookPortraitTexture;
	Texture* m_hitBoxTexture;
	Sprite* m_mookPortraitSprite;
	Sprite* m_kingMookPortraitSprite;
};