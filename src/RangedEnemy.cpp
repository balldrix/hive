#define NOMINMAX
#include "RangedEnemy.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "DamageData.h"
#include "Enemy.h"
#include "EnemyAttackState.h"
#include "EnemyDefinition.h"
#include "EventManager.h"
#include "FireProjectileEvent.h"
#include "NPCManager.h"
#include "Player.h"
#include "ProjectileManager.h"
#include "Randomiser.h"
#include "Sound.h"
#include "SoundSource.h"
#include "State.h"
#include "StateMachine.h"
#include "Texture.h"

#include <algorithm>
#include <directxtk/SimpleMath.h>
#include <string>

using namespace DirectX;

namespace
{
	constexpr float ProjectileAimHeightOffset = 2.0f;

	void FillAttackSounds(std::string (&attackSounds)[5])
	{
		attackSounds[0] = "wasteLobsterAttack_001";
		attackSounds[1] = "wasteLobsterAttack_002";
		attackSounds[2] = "wasteLobsterAttack_003";
		attackSounds[3] = "wasteLobsterAttack_004";
		attackSounds[4] = "wasteLobsterAttack_005";
	}
}

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
	FillAttackSounds(m_attackSounds);

	eventManager->RegisterEvent("FireProjectile", id, new FireProjectileEvent(this));
}

void RangedEnemy::Reset(const std::string& id)
{
	Enemy::Reset(id);
	FillAttackSounds(m_attackSounds);

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

	auto directionToTarget = GetPlayerTarget()->GetPosition().x - m_position.x;
	FlipHorizontally(directionToTarget < 0);

	DamageData damageData = GetDamageData();
	Vector2 targetPosition = m_playerTarget->GetGroundPosition();
	targetPosition.y -= ProjectileAimHeightOffset;

	Vector2 direction = targetPosition - m_groundPosition;
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

	const int randomSoundIndex = Randomiser::GetRandNumUniform(0, 4);
	Sound* sound = AssetLoader::GetSound(m_attackSounds[randomSoundIndex]);
	if(sound != nullptr)
	{
		m_attackSoundSource->Play(sound);
	}
}
