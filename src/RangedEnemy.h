#pragma once

#include "Enemy.h"
#include "EnemyDefinition.h"
#include "State.h"

#include <string>

class Camera;
class Player;
class CutsceneManager;
class EventManager;
class NPCManager;
class Texture;
class ProjectileManager;

class RangedEnemy : public Enemy
{
public:
	RangedEnemy();
	~RangedEnemy();
	void Init(const std::string& id,
		Camera* camera,
		Player* player,
		CutsceneManager* cutsceneManager, EventManager* eventManager,
		const EnemyDefinition& definition,
		NPCManager* npcManager,
		Texture* shadowTexture, State<Enemy>* globalEnemyState, State<Enemy>* startingState,
		ProjectileManager* projectileManager);
	void Reset(const std::string& id) override;

	void Attack() override;
	void FireProjectile();

private:
	ProjectileManager* m_projectileManager;
	std::string m_attackSounds[5];
};
