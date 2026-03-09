#define NOMINMAX
#include "RangedEnemy.h"

#include "Camera.h"
#include "Enemy.h"
#include "EnemyAttackState.h"
#include "EnemyDefinition.h"
#include "EventManager.h"
#include "NPCManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "Randomiser.h"
#include "State.h"
#include "StateMachine.h"
#include "Texture.h"

#include <algorithm>
#include <string>

RangedEnemy::RangedEnemy()
{
}

RangedEnemy::~RangedEnemy()
{
}

void RangedEnemy::Init(const std::string& id, Camera* camera, Player* player, CutsceneManager* cutsceneManager, EventManager* eventManager, const EnemyDefinition& definition, NPCManager* npcManager, Texture* shadowTexture, State<Enemy>* globalEnemyState, State<Enemy>* startingState, ProjectileManager* projectileManager)
{
	Enemy::Init(id, camera, player, cutsceneManager, eventManager, definition, npcManager, shadowTexture, globalEnemyState, startingState);
	m_projectileManager = projectileManager;
}

void RangedEnemy::Attack()
{
	if(m_enemyDefinition.damageData.empty())
	{
		return;
	}

	int attackNum = Randomiser::GetRandNumUniform(0, static_cast<int>(m_enemyDefinition.damageData.size()) - 1);
	const auto& damageData = m_enemyDefinition.damageData[attackNum];

	EnemyAttackState::Instance()->SetAttack(damageData.name);
	m_stateMachine->ChangeState(EnemyAttackState::Instance());

	if(m_projectileManager == nullptr || m_playerTarget == nullptr)
	{
		return;
	}

	Vector2 direction = m_playerTarget->GetGroundPosition() - m_groundPosition;
	if(direction.LengthSquared() > 0.0001f)
	{
		direction.Normalize();
	}
	else
	{
		direction = Vector2::UnitX;
	}

	float projectileSpeed = std::max(60.0f, m_enemyDefinition.runningSpeed);
	Vector2 spawnPosition = m_position + direction * 8.0f;
	m_projectileManager->SpawnProjectile(spawnPosition, direction, projectileSpeed, damageData.amount, 2.0f, this);
}
