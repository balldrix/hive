#define NOMINMAX
#include "RangedEnemy.h"

#include "Camera.h"
#include "Enemy.h"
#include "EnemyAttackState.h"
#include "EnemyDefinition.h"
#include "EventManager.h"
#include "FireProjectileEvent.h"
#include "NPCManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "State.h"
#include "StateMachine.h"
#include "Texture.h"

#include <algorithm>
#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX;

RangedEnemy::RangedEnemy() :
	m_projectileManager(nullptr)
{
}

RangedEnemy::~RangedEnemy()
{
}

void RangedEnemy::Init(const std::string& id, Camera* camera, Player* player, CutsceneManager* cutsceneManager, EventManager* eventManager, const EnemyDefinition& definition, NPCManager* npcManager, Texture* shadowTexture, State<Enemy>* globalEnemyState, State<Enemy>* startingState, ProjectileManager* projectileManager)
{
	Enemy::Init(id, camera, player, cutsceneManager, eventManager, definition, npcManager, shadowTexture, globalEnemyState, startingState);
	m_projectileManager = projectileManager;

	eventManager->RegisterEvent("FireProjectile", id, new FireProjectileEvent(this));
}

void RangedEnemy::Reset(const std::string& id)
{
	Enemy::Reset(id);

	if(m_eventManager == nullptr)
	{
		return;
	}

	m_eventManager->RegisterEvent("FireProjectile", id, new FireProjectileEvent(this));
}

void RangedEnemy::Attack()
{
	if(m_enemyDefinition.damageData.empty())
	{
		return;
	}

	const auto& damageData = m_enemyDefinition.damageData.front();

	EnemyAttackState::Instance()->SetAttack(damageData.name);
	m_stateMachine->ChangeState(EnemyAttackState::Instance());
}

void RangedEnemy::FireProjectile()
{
	if(m_projectileManager == nullptr || m_playerTarget == nullptr)
	{
		return;
	}

	DamageData damageData = GetDamageData();
	Vector2 direction = m_playerTarget->GetGroundPosition() - m_groundPosition;
	if(direction.LengthSquared() > 0.0001f)
	{
		direction.Normalize();
	}
	else
	{
		direction = Vector2::UnitX;
	}

	float projectileSpeed = std::max(90.0f, m_enemyDefinition.runningSpeed);
	float horizontalOffset = GetFacingDirection().x < 0.0f ? -24.0f : 24.0f;
	Vector2 spawnPosition = m_position + Vector2(horizontalOffset, -20.0f);
	m_projectileManager->SpawnProjectile(spawnPosition, direction, projectileSpeed, damageData.amount, 2.0f, this);
}
