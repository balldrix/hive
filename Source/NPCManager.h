// NPCManager.h
// Christopher Ball 2019
// initialises and spawns the npc enemies

#ifndef _NPC_MANAGER_H_
#define _NPC_MANAGER_H_

#include "pch.h"
#include "EnemyDataContainer.h"

class Graphics;
class Enemy;

class NPCManager
{
public:
	~NPCManager();
	NPCManager();

	void	Init();
	bool	InitTypes(std::string fileName);
	bool	InitNPCs(std::string fileName);

	void	Render(Graphics* graphics);
	void	Update(float deltaTime);

	void	Reset();
	void	DeleteAll();

	std::vector<Enemy*> GetEnemyList() const { return m_enemyList; }

private:
	std::vector<Enemy*>		m_enemyList;
	EnemyDataContainer*		m_enemyDataContainer;
};

#endif // !_NPC_MANAGER_H_
