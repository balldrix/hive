// NPCManager.h
// Christopher Ball 2019
// initialises and spawns the npc enemies

#ifndef _NPC_MANAGER_H_
#define _NPC_MANAGER_H_

#include "pch.h"
#include "EnemyDataContainer.h"

class Camera;
class Enemy;
class Graphics;
class InGameHudManager;
class NPCFactory;
class Player;

class NPCManager
{
public:
	~NPCManager();
	NPCManager();

	void	Init(Graphics* graphics, Camera* camera, Player* player, InGameHudManager* hudManager, Texture* standardShadowTexture,
				 Texture* hitBoxTexture);
	bool	InitTypes(std::string fileName);
	bool	InitNPCs(Graphics* graphics, Camera* camera, Player* player, InGameHudManager* hudManager, Texture* standardShadowTexture,
					 Texture* hitBoxTexture, std::string enemyDataFile);

	void	Render(Graphics* graphics);
	void	Update(float deltaTime);

	void	Reset();
	void	DeleteAll();

	std::vector<Enemy*> GetEnemyList() const { return m_enemyList; }

private:
	NPCFactory*				m_NPCFactory;
	std::vector<Enemy*>		m_enemyList;
	EnemyDataContainer*		m_enemyDataContainer;
};

#endif // !_NPC_MANAGER_H_
