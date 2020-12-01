// Christopher Ball 2019-2020

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
	void DeleteAll();
	void ReleaseAll();

	Graphics* m_graphics;
	Camera* m_camera;
	Player* m_player;
	InGameHudManager* m_hudManager;
	Texture* m_mookTexture;
	Texture* m_standardShadowTexture;
	Texture* m_mookPortraitTexture;
	Texture* m_hitBoxTexture;
	Sprite* m_mookPortraitSprite;
	Enemy* m_mook;
};