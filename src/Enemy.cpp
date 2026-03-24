#include "Enemy.h"

#include "AnimatedSpriteData.h"
#include "Animator.h"
#include "AssetLoader.h"
#include "AudioEngine.h"
#include "Camera.h"
#include "CutsceneManager.h"
#include "DamageData.h"
#include "DustFXEvent.h"
#include "EnemyAttackState.h"
#include "EnemyDefinition.h"
#include "EnemyHurtState.h"
#include "EnemyIdleState.h"
#include "EnemyKnockbackState.h"
#include "EnemyStunnedState.h"
#include "EventManager.h"
#include "GameDataManager.h"
#include "GameObject.h"
#include "GameplayConstants.h"
#include "Graphics.h"
#include "HitBoxData.h"
#include "HitBoxManager.h"
#include "LevelCollision.h"
#include "MoveNPCEvent.h"
#include "NPCManager.h"
#include "PlayAnimationEvent.h"
#include "Player.h"
#include "PlaySoundEvent.h"
#include "Randomiser.h"
#include "Sound.h"
#include "SoundSource.h"
#include "Sprite.h"
#include "SpriteFx.h"
#include "SpriteSheet.h"
#include "State.h"
#include "StateMachine.h"
#include "Texture.h"
#include "UIBarView.h"
#include "UIManager.h"
#include "UIPortraitView.h"
#include "UnitVectors.h"

#include <DirectXMath.h>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <cmath>
#include <string>
#include <vector>

using namespace GameplayConstants;

namespace
{
	constexpr float IdleAvoidDistance = 24.0f;
	constexpr float IdleSeparationSpeedMultiplier = 0.5f;
	constexpr float AttackPreviewStep = 1.0f;
	constexpr float AttackSideBuffer = 1.0f;
	constexpr float RangedRetreatRangeMultiplier = 0.6f;
	constexpr float RangedPreferredRangeMultiplier = 0.8f;
	constexpr float RangedVerticalCorrectionWeight = 0.35f;
	constexpr float RangedAvoidDistance = 20.0f;
	constexpr float RangedAvoidWeight = 1.25f;
	constexpr float DefaultStunDuration = 2.0f;
	constexpr float DefaultKnockbackForce = 80.0f;
}

Enemy::Enemy() :
	m_waveId(""),
	m_preparedAttackName(""),
	m_playerTarget(nullptr),
	m_stateMachine(nullptr),
	m_portraitSprite(nullptr),
	m_vocalSoundSource(nullptr),
	m_footStepSoundSource(nullptr),
	m_attackSoundSource(nullptr),
	m_stateChangeTimer(0.0f),
	m_stunTimer(0.0f),
	m_flashingTimer(0.0f),
	m_isFlashing(false),
	m_recoverAfterKnockback(false),
	m_recentFootstepFrame(0),
	m_startingState(nullptr),
	m_npcManager(nullptr),
	m_cutsceneManager(nullptr)
{}

Enemy::~Enemy()
{
	DeleteAll();
}

void Enemy::DeleteAll()
{
	m_eventManager->UnRegisterAllForTarget(m_id);

	AudioEngine::Instance()->RemoveSoundSource(m_impactSoundSource);
	AudioEngine::Instance()->RemoveSoundSource(m_attackSoundSource);
	AudioEngine::Instance()->RemoveSoundSource(m_footStepSoundSource);
	AudioEngine::Instance()->RemoveSoundSource(m_vocalSoundSource);

	delete m_impactSoundSource;
	delete m_attackSoundSource;
	delete m_footStepSoundSource;
	delete m_vocalSoundSource;
	delete m_dustFx;
	delete m_stateMachine;
	delete m_hitBoxManager;
	delete m_animator;
	delete m_shadow;
	delete m_spritesheet;

	m_startingState = nullptr;
	m_impactSoundSource = nullptr;
	m_attackSoundSource = nullptr;
	m_footStepSoundSource = nullptr;
	m_vocalSoundSource = nullptr;
	m_dustFx = nullptr;
	m_stateMachine = nullptr;
	m_hitBoxManager = nullptr;
	m_animator = nullptr;
	m_shadow = nullptr;
	m_spritesheet = nullptr;
}

void Enemy::Init(const std::string& id,
	Camera* camera,
	Player* player,
	CutsceneManager* cutsceneManager, EventManager* eventManager,
	const EnemyDefinition& data,
	NPCManager* npcManager,
	Texture* shadowTexture, State<Enemy>* globalEnemyState, State<Enemy>* startingState)
{
	m_id = id;
	m_camera = camera;
	m_playerTarget = player;
	m_cutsceneManager = cutsceneManager;
	m_eventManager = eventManager;
	m_enemyDefinition = data;
	m_npcManager = npcManager;
	m_grounded = true;

	m_collisionMask = WorldAndObjects;

	AnimatedSpriteData animatedSpriteData;
	animatedSpriteData = GameDataManager::LoadAnimatedSpriteData(data.spritesheetDataPath);

	m_spritesheet = new Spritesheet();
	m_spritesheet->Init(AssetLoader::GetTexture(data.textureId), animatedSpriteData.spriteFrameData);
	m_spritesheet->SetOrigin(m_enemyDefinition.spriteOrigin);

	m_shadow = new Sprite();
	m_shadow->Init(shadowTexture);
	m_shadow->SetAlpha(0.7f);

	m_animator = new Animator();
	m_animator->Init(m_id, animatedSpriteData, m_eventManager);
	m_animator->SetAnimation(0);
	
	std::vector<HitBoxData> hitboxData;
	hitboxData = GameDataManager::LoadHitboxData(data.hitBoxDataPath);

	m_hitBoxManager = new HitBoxManager();
	m_hitBoxManager->Init(this, hitboxData);

	m_movementSpeed = data.walkSpeed;
	m_acceleration = data.acceleration;
	m_deceleration = data.deceleration;

	m_startingState = startingState;
	m_stateMachine = new StateMachine<Enemy>(this);
	m_stateMachine->Init(EnemyIdleState::Instance(), nullptr, globalEnemyState);
	m_stateMachine->ChangeState(startingState);

	m_health = m_enemyDefinition.hp;

	m_dustFx = new SpriteFx();
	m_dustFx->Init("t_dust", "dustfx", Vector2(20.0f, 30.0f));

	m_vocalSoundSource = new SoundSource();
	m_vocalSoundSource->SetTarget(this);
	m_vocalSoundSource->SetLooping(false);
	m_vocalSoundSource->SetRelative(false);

	m_footStepSoundSource = new SoundSource();
	m_footStepSoundSource->SetTarget(this);
	m_footStepSoundSource->SetLooping(true);
	m_footStepSoundSource->SetRelative(false);

	m_attackSoundSource = new SoundSource();
	m_attackSoundSource->SetTarget(this);
	m_attackSoundSource->SetLooping(false);
	m_attackSoundSource->SetRelative(false);

	m_impactSoundSource = new SoundSource();
	m_impactSoundSource->SetTarget(this);
	m_impactSoundSource->SetLooping(false);
	m_impactSoundSource->SetRelative(false);

	AudioEngine::Instance()->AddSoundSource(m_vocalSoundSource, false);
	AudioEngine::Instance()->AddSoundSource(m_footStepSoundSource, false);
	AudioEngine::Instance()->AddSoundSource(m_attackSoundSource, true);
	AudioEngine::Instance()->AddSoundSource(m_impactSoundSource, false);

	m_impactSounds =
	{
		"enemyImpact_001",
		"enemyImpact_002",
		"enemyImpact_003",
		"enemyImpact_004",
		"enemyImpact_005",
		"enemyImpact_006",
		"enemyImpact_007",
		"enemyImpact_008"
	};

	ResetStateChangeTimer();

	m_active = false;
}

void Enemy::Update(float deltaTime)
{
	if(!m_active) return;
	if(!m_cutsceneManager->IsActive()) m_stateMachine->Update();

	GameObject::Update(deltaTime);

	if(m_stateChangeTimer > 0.0f) m_stateChangeTimer -= deltaTime;
	if(m_stunTimer > 0.0f) m_stunTimer -= deltaTime;
	if(m_flashingTimer > 0.0f) m_flashingTimer -= deltaTime;

	if(m_isFlashing && m_flashingTimer <= 0.0f)
	{
		auto isSpriteEnabled = m_spritesheet->GetEnabled();
		isSpriteEnabled ? m_spritesheet->DisableSprite() : m_spritesheet->EnableSprite();
		m_flashingTimer = EnemyFlashDuration;
	}

	m_hitBoxManager->Update(m_animator->GetCurrentFrame());

	if(!m_dead) return;

	m_deathTimer -= deltaTime;
	if(m_deathTimer <= 0.0f)
	{
		m_active = false;
	}
}

void Enemy::Render(Graphics* graphics)
{
	if(!m_active) return;

	if(m_shadow)
	{
		m_shadow->SetDepth(m_groundPosition.y / graphics->GetBackbufferHeight() - 0.1f);
		m_shadow->Render(graphics);
	}

	if(m_spritesheet)
	{
		m_spritesheet->SetDepth(m_groundPosition.y / graphics->GetBackbufferHeight());

		if(m_animator)
		{
			int frameNum = m_animator->GetCurrentFrame() + m_animator->GetAnimation().from;
			m_spritesheet->Render(graphics, frameNum);
		}
		else
		{
			m_spritesheet->Render(graphics, 0);
		}
	}

	//	render hitbox
	if(m_hitBoxManager)
		m_hitBoxManager->Render(graphics, m_camera);

	if(m_dustFx)
		m_dustFx->Render(graphics);
}

void Enemy::Reset(const std::string& id)
{
	if (m_eventManager != nullptr && !m_id.empty())
	{
		m_eventManager->UnRegisterAllForTarget(m_id);
	}

	ClearPreparedAttack();
	m_stunTimer = 0.0f;
	m_recoverAfterKnockback = false;

	// Keep the animator's event owner id aligned with pooled enemy ids.
	SetID(id);
}

void Enemy::Spawn(const Vector2& position, std::string waveId)
{
	m_waveId = waveId;
	m_position = position;
	m_groundPosition = position;
	m_dead = false;
	m_active = true;
	m_isFlashing = false;
	m_health = m_enemyDefinition.hp;
	ClearPreparedAttack();
	m_stunTimer = 0.0f;
	m_recoverAfterKnockback = false;

	GetSprite()->EnableSprite();
	m_stateMachine->ChangeState(m_startingState);
	RegisterEvents();
}

void Enemy::SetDead(bool isDead)
{
	m_dead = isDead;
}

void Enemy::SetPlayerTarget(Player* player)
{
	m_playerTarget = player;
}

void Enemy::ResetStateChangeTimer()
{
	m_stateChangeTimer = Randomiser::GetRandNumUniform(m_enemyDefinition.minStateChangeTime, m_enemyDefinition.maxStateChangeTime);
}

void Enemy::ApplyDamage(GameObject* source, const int& amount)
{
	DamageData damageData;
	damageData.amount = amount;
	ApplyDamage(source, damageData);
}

void Enemy::ApplyDamage(GameObject* source, const DamageData& damageData)
{
	m_health -= damageData.amount;

	if(m_health < 0) m_health = 0;

	PlayImpactSound();
	ClearPreparedAttack();

	if(m_health == 0)
	{
		if(IsCurrentWaveAttacker())
		{
			NPCManager::Instance()->SetNextAttackingEnemy(this);
		}

		m_recoverAfterKnockback = false;
		m_stateMachine->ChangeState(EnemyKnockbackState::Instance());
		Knockback(GetKnockbackDirectionFromSource(source), 100.0f);
		SetKnockbackCount(1);
		return;
	}

	if(damageData.attackEffect == AttackEffect::Knockback)
	{
		if(IsCurrentWaveAttacker())
		{
			NPCManager::Instance()->SetNextAttackingEnemy(this);
		}

		m_recoverAfterKnockback = true;
		m_stateMachine->ChangeState(EnemyKnockbackState::Instance());
		Knockback(
			GetKnockbackDirectionFromSource(source),
			damageData.knockbackForce > 0.0f ? damageData.knockbackForce : DefaultKnockbackForce);
		SetKnockbackCount(damageData.knockbackCount);
		return;
	}

	if(damageData.attackEffect == AttackEffect::Stun)
	{
		Stun(damageData.effectDuration);
		return;
	}

	m_stateMachine->ChangeState(EnemyHurtState::Instance());
}

void Enemy::Knockback(const Vector2& direction, const float& force)
{
	SetVelocity(direction);
	SetMovementSpeed(force);
}

void Enemy::Stun(float duration)
{
	if(IsCurrentWaveAttacker())
	{
		NPCManager::Instance()->SetNextAttackingEnemy(this);
	}

	m_stunTimer = duration > 0.0f ? duration : DefaultStunDuration;
	m_stateMachine->ChangeState(EnemyStunnedState::Instance());
}

void Enemy::Attack()
{
	if(m_enemyDefinition.damageData.empty())
	{
		return;
	}

	const std::string attackName = GetPreparedAttackName();
	EnemyAttackState::Instance()->SetAttack(attackName);
	m_stateMachine->ChangeState(EnemyAttackState::Instance());
	ClearPreparedAttack();
	NPCManager::Instance()->SetNextAttackingEnemy(this);
}

void Enemy::Kill()
{
	m_dead = true;
	m_deathTimer = EnemyDeadDuration;
}

void Enemy::ProcessSteering()
{
	if(IsRangedEnemy())
	{
		ProcessRangedSteering();
		return;
	}

	if(IsNormalMeleeEnemy() && IsCurrentWaveAttacker())
	{
		const float distance = (GetPosition() - GetPlayerTarget()->GetPosition()).Length();

		if(distance <= m_enemyDefinition.fightRange)
		{
			m_targetVelocity = GetAttackApproachVelocity();
			return;
		}
	}

	m_targetVelocity = Vector2::Zero;
	m_targetVelocity += Seek() * 2.0f;
	m_targetVelocity += Avoid(MinEnemyAvoidDistance, true);

	// Ranged enemies should hold lanes and shoot rather than orbiting the player.
	if(m_enemyDefinition.enemyType != EnemyType::Ranged)
	{
		m_targetVelocity += Strafe() * 0.5f;
	}

	if(m_targetVelocity.LengthSquared() > 0.0001f)
	{
		m_targetVelocity.Normalize();
	}
	else
	{
		m_targetVelocity = Vector2::Zero;
	}
}

void Enemy::ProcessRunningSteering()
{
	if(!IsNormalMeleeEnemy())
	{
		ProcessSteering();
		return;
	}

	Vector2 direction = Vector2::Zero;
	const float deltaX = m_playerTarget->GetPositionX() - GetPositionX();

	if(fabs(deltaX) > 0.5f)
	{
		direction.x = deltaX > 0.0f ? 1.0f : -1.0f;
	}

	direction += Avoid(MinEnemyAvoidDistance, false);

	if(direction.LengthSquared() > 0.0001f)
	{
		direction.Normalize();
	}

	m_targetVelocity = direction;
}

void Enemy::ProcessRangedSteering()
{
	const float distance = (GetPosition() - GetPlayerTarget()->GetPosition()).Length();
	const bool shouldRetreat = ShouldRangedRetreat(distance);
	Vector2 direction = GetRangedPositioningVelocity(distance);
	direction += Avoid(RangedAvoidDistance, false) * RangedAvoidWeight;

	SetMovementSpeed(shouldRetreat ? m_enemyDefinition.runningSpeed : m_enemyDefinition.walkSpeed);

	if(direction.LengthSquared() > 0.0001f)
	{
		direction.Normalize();
	}

	m_targetVelocity = direction;
}

void Enemy::ProcessIdleSeparation()
{
	Vector2 separation = Avoid(IdleAvoidDistance, false);

	SetMovementSpeed(m_enemyDefinition.walkSpeed * IdleSeparationSpeedMultiplier);

	if(separation.LengthSquared() > 0.0001f)
	{
		separation.Normalize();
		SetTargetVelocity(separation);
		return;
	}

	Stop();
}

void Enemy::Flash()
{
	if(!m_isFlashing) m_isFlashing = true;
}

bool Enemy::IsNormalMeleeEnemy() const
{
	return m_enemyDefinition.enemyType == EnemyType::Normal;
}

bool Enemy::IsRangedEnemy() const
{
	return m_enemyDefinition.enemyType == EnemyType::Ranged;
}

bool Enemy::IsCurrentWaveAttacker() const
{
	return NPCManager::Instance()->IsAttackingEnemy(this);
}

bool Enemy::IsWithinAttackVerticalRange() const
{
	return fabs(m_groundPosition.y - m_playerTarget->GetGroundPosition().y) < VerticalHitRange;
}

bool Enemy::CanPreparedAttackHitPlayer()
{
	return CanPreparedAttackHitPlayerAt(GetPosition());
}

bool Enemy::CanPreparedAttackHitPlayerAt(const Vector2& position)
{
	if(m_playerTarget == nullptr || m_hitBoxManager == nullptr || m_spritesheet == nullptr)
	{
		return false;
	}

	const std::string attackName = GetPreparedAttackName();
	if(attackName.empty())
	{
		return false;
	}

	return m_hitBoxManager->WouldHitTarget(
		attackName,
		m_playerTarget->GetHitBoxManager()->GetHurtBox(),
		position,
		m_spritesheet->GetOrigin(),
		ShouldFaceLeftAt(position));
}

void Enemy::ClearPreparedAttack()
{
	m_preparedAttackName.clear();
}

float Enemy::GetRangedRetreatRange() const
{
	return m_enemyDefinition.attackRange * RangedRetreatRangeMultiplier;
}

float Enemy::GetRangedPreferredRange() const
{
	return m_enemyDefinition.attackRange * RangedPreferredRangeMultiplier;
}

bool Enemy::ShouldRangedRetreat(float distanceToPlayer) const
{
	return distanceToPlayer < GetRangedRetreatRange();
}

Vector2 Enemy::Seek() const
{
	Vector2 direction = Vector2::Zero;
	Vector2 targetPosition = GetPlayerTarget()->GetPosition();
	Vector2 position = GetPosition();

	direction = targetPosition - position;

	if(direction.Length() < m_enemyDefinition.attackRange)
		direction = -direction;

	if(direction.LengthSquared() > 0.0001f)
	{
		direction.Normalize();
	}
	else
	{
		direction = Vector2::Zero;
	}

	return direction;
}

Vector2 Enemy::Avoid(float minDistance, bool ignoreIfAttackingEnemy) const
{
	Vector2 force = Vector2::Zero;
	const bool isRangedSelf = IsRangedEnemy();

	if(ignoreIfAttackingEnemy && NPCManager::Instance()->IsAttackingEnemy(this)) return force;

	auto enemyList = m_npcManager->GetEnemyList();

	for(auto it = enemyList.begin(); it != enemyList.end(); it++)
	{
		if(*it == this || !(*it)->IsActive()) continue;

		if(isRangedSelf)
		{
			if((*it)->GetData().enemyType != EnemyType::Ranged) continue;
		}
		else if((*it)->GetWaveId() != m_waveId)
		{
			continue;
		}

		auto toOther = m_position - (*it)->GetPosition();
		float distance = toOther.Length();

		if(distance > minDistance) continue;
		if(distance <= 0.0001f) continue;

		force += toOther / distance;
	}

	return force;
}

Vector2 Enemy::Strafe() const
{
	if(NPCManager::Instance()->IsAttackingEnemy(this)) return Vector2::Zero;

	auto toTarget = m_playerTarget->GetPosition() - GetPosition();
	auto crossProduct = Vector2(toTarget.y, -toTarget.x);
	if(crossProduct.LengthSquared() > 0.0001f)
	{
		crossProduct.Normalize();
	}
	else
	{
		return Vector2::Zero;
	}
	return crossProduct;
}

Vector2 Enemy::GetRangedPositioningVelocity(float distanceToPlayer) const
{
	Vector2 direction = Vector2::Zero;
	const Vector2 toPlayer = m_playerTarget->GetPosition() - GetPosition();
	const float verticalDistance = m_playerTarget->GetPositionY() - GetPositionY();

	if(distanceToPlayer < GetRangedPreferredRange())
	{
		direction.x = toPlayer.x < 0.0f ? 1.0f : -1.0f;
	}
	else if(distanceToPlayer > m_enemyDefinition.attackRange)
	{
		direction.x = toPlayer.x < 0.0f ? -1.0f : 1.0f;
	}

	if(fabs(verticalDistance) > VerticalHitRange)
	{
		direction.y = (verticalDistance > 0.0f ? 1.0f : -1.0f) * RangedVerticalCorrectionWeight;
	}

	if(direction.LengthSquared() > 0.0001f)
	{
		direction.Normalize();
	}

	return direction;
}

Vector2 Enemy::GetAttackApproachVelocity()
{
	Vector2 direction = Vector2::Zero;
	const Vector2 currentPosition = GetPosition();
	const float playerX = m_playerTarget->GetPositionX();
	const float playerY = m_playerTarget->GetPositionY();
	const bool isLeftSide = currentPosition.x <= playerX;
	const float boundaryX = playerX + (isLeftSide ? -AttackSideBuffer : AttackSideBuffer);
	const float sideLimitX = playerX + (isLeftSide ? -m_enemyDefinition.fightRange : m_enemyDefinition.fightRange);
	const float maxSearchDistance = fabs(sideLimitX - boundaryX);

	float targetX = currentPosition.x;
	bool foundTargetX = CanPreparedAttackHitPlayerAt(currentPosition);

	if(!foundTargetX)
	{
		for(float offset = AttackPreviewStep; offset <= maxSearchDistance; offset += AttackPreviewStep)
		{
			const float towardPlayerX = currentPosition.x + (isLeftSide ? offset : -offset);
			const bool isTowardPlayerCandidateValid = isLeftSide ? towardPlayerX <= boundaryX : towardPlayerX >= boundaryX;

			if(isTowardPlayerCandidateValid &&
				CanPreparedAttackHitPlayerAt(Vector2(towardPlayerX, currentPosition.y)))
			{
				targetX = towardPlayerX;
				foundTargetX = true;
				break;
			}

			const float awayFromPlayerX = currentPosition.x + (isLeftSide ? -offset : offset);
			const bool isAwayCandidateValid = isLeftSide ? awayFromPlayerX >= sideLimitX : awayFromPlayerX <= sideLimitX;

			if(isAwayCandidateValid &&
				CanPreparedAttackHitPlayerAt(Vector2(awayFromPlayerX, currentPosition.y)))
			{
				targetX = awayFromPlayerX;
				foundTargetX = true;
				break;
			}
		}
	}

	const float deltaX = targetX - currentPosition.x;
	const float deltaY = playerY - currentPosition.y;

	if(fabs(deltaX) > 0.5f)
	{
		direction.x = deltaX > 0.0f ? 1.0f : -1.0f;
	}
	else if(!foundTargetX)
	{
		direction.x = isLeftSide ? -1.0f : 1.0f;
	}

	if(fabs(deltaY) > VerticalHitRange)
	{
		direction.y = deltaY > 0.0f ? 1.0f : -1.0f;
	}

	if(direction.LengthSquared() > 0.0001f)
	{
		direction.Normalize();
	}

	return direction;
}

Vector2 Enemy::GetKnockbackDirectionFromSource(GameObject* source) const
{
	if(source == nullptr)
	{
		return GetFacingDirection().x < 0.0f ? UnitVectors::UpRight : UnitVectors::UpLeft;
	}

	if(GetPositionX() < source->GetPositionX())
	{
		return UnitVectors::UpLeft;
	}

	return UnitVectors::UpRight;
}

std::string Enemy::GetPreparedAttackName()
{
	if(m_preparedAttackName.empty() && !m_enemyDefinition.damageData.empty())
	{
		const int attackNum = Randomiser::GetRandNumUniform(0, (int)m_enemyDefinition.damageData.size() - 1);
		m_preparedAttackName = m_enemyDefinition.damageData[attackNum].name;
	}

	return m_preparedAttackName;
}

bool Enemy::ShouldFaceLeftAt(const Vector2& position) const
{
	return m_playerTarget != nullptr && m_playerTarget->GetPositionX() < position.x;
}

void Enemy::ShowEnemyHud()
{
	UIPortraitView* portraitView = static_cast<UIPortraitView*>(UIManager::GetView("Enemy Portrait"));

	if(portraitView)
	{
		portraitView->SetActive(true);
		portraitView->SetPortraitTexture(AssetLoader::GetTexture(fmt::format("t_{0}_portrait", m_enemyDefinition.id)));
	}

	UIBarView* healthbar = static_cast<UIBarView*>(UIManager::GetView("Enemy Health Bar"));

	if(healthbar)
	{
		healthbar->SetActive(true);
		healthbar->SetCurrentValue((float)m_health, true);
		healthbar->SetMaxValue((float)m_enemyDefinition.hp);
	}
}

void Enemy::PlaySound(const std::string& id)
{
	Sound* sound = AssetLoader::GetSound(id);

	if(sound == nullptr) return;

	m_attackSoundSource->Play(sound);
}

void Enemy::ApplyFacingDirection()
{
	auto isInKnockbackState = m_stateMachine->IsInState(*EnemyKnockbackState::Instance());

	// true if moving to the left
	if(m_currentVelocity.x < 0)
	{
		FlipHorizontally(!isInKnockbackState);
	}

	// true if moving to the right
	if(m_currentVelocity.x > 0)
	{
		FlipHorizontally(isInKnockbackState);
	}
}

void Enemy::RegisterEvents()
{
	m_eventManager->RegisterEvent("PlaySound", m_id, new PlaySoundEvent(m_attackSoundSource));
	m_eventManager->RegisterEvent("MoveNPC", m_id, new MoveNPCEvent(this));
	m_eventManager->RegisterEvent("PlayAnimation", m_id, new PlayAnimationEvent(m_animator));
	m_eventManager->RegisterEvent("PlayDustFX", m_id, new DustFXEvent(this));
}

DamageData Enemy::GetDamageData() const
{
	std::string stateName = m_stateMachine->GetCurrentState()->GetName();
	
	for(const auto& data : m_enemyDefinition.damageData)
	{
		if(data.name == stateName) return data;
	}
	
	return DamageData();
}
