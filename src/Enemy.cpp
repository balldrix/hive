#include "Enemy.h"

#include "AnimatedSpriteData.h"
#include "Animator.h"
#include "AssetLoader.h"
#include "AudioEngine.h"
#include "DamageData.h"
#include "EnemyAttackState.h"
#include "EnemyData.h"
#include "EnemyHurtState.h"
#include "EnemyIdleState.h"
#include "EnemyKnockbackState.h"
#include "GameDataManager.h"
#include "GameObject.h"
#include "GameplayConstants.h"
#include "Graphics.h"
#include "HitBoxData.h"
#include "HitBoxManager.h"
#include "Logger.h"
#include "NPCManager.h"
#include "Player.h"
#include "Randomiser.h"
#include "Sound.h"
#include "SoundManager.h"
#include "SoundSource.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "State.h"
#include "StateMachine.h"
#include "Texture.h"
#include "UIBarView.h"
#include "UIManager.h"
#include "UIPortraitView.h"
#include "UnitVectors.h"

#include "SpriteFx.h"
#include <cstdint>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <string>
#include <vector>

using namespace GameplayConstants;

Enemy::Enemy() :
	m_playerTarget(nullptr),
	m_stateMachine(nullptr),
	m_portraitSprite(nullptr),
	m_hitBoxSprite(nullptr),
	m_vocalSoundSource(nullptr),
	m_footStepsSoundSource(nullptr),
	m_punchSoundSource(nullptr),
	m_thinkingTimer(0.0f),
	m_flashingTimer(0.0f),
	m_isHostile(false),
	m_isFlashing(false),
	m_recentFootstepFrame(0),
	m_startingState(nullptr),
	m_npcManager(nullptr)
{}

Enemy::~Enemy()
{
	DeleteAll();
}

void Enemy::DeleteAll()
{
	AudioEngine::Instance()->RemoveSoundSource(m_punchSoundSource);
	AudioEngine::Instance()->RemoveSoundSource(m_footStepsSoundSource);
	AudioEngine::Instance()->RemoveSoundSource(m_vocalSoundSource);

	delete m_punchSoundSource;
	delete m_footStepsSoundSource;
	delete m_vocalSoundSource;
	delete m_dustFx;
	delete m_stateMachine;
	delete m_hitBoxManager;
	delete m_hitBoxSprite;
	delete m_animator;
	delete m_shadow;
	delete m_spritesheet;

	m_startingState = nullptr;
	m_punchSoundSource = nullptr;
	m_footStepsSoundSource = nullptr;
	m_vocalSoundSource = nullptr;
	m_dustFx = nullptr;
	m_stateMachine = nullptr;
	m_hitBoxManager = nullptr;
	m_hitBoxSprite = nullptr;
	m_animator = nullptr;
	m_shadow = nullptr;
	m_spritesheet = nullptr;
}

void Enemy::Init(Graphics* graphics,
				Camera* camera,
				Player* player,
				const EnemyData& data,
				NPCManager* npcManager,
				Texture* shadowTexture,
				State<Enemy>* globalEnemyState,
				State<Enemy>* startingState)
{
	m_camera = camera;
	m_playerTarget = player;
	m_enemyData = data;
	m_position = data.objectData.startingPosition;
	m_groundPosition = data.objectData.startingPosition;
	m_npcManager = npcManager;
	m_grounded = true;

	AnimatedSpriteData animatedSpriteData;
	animatedSpriteData = GameDataManager::LoadAnimatedSpriteData(data.name);

	m_spritesheet = new Spritesheet();
	m_spritesheet->Init(AssetLoader::GetTexture(fmt::format("t_{}", data.name)), animatedSpriteData.spriteFrameData);
	m_spritesheet->SetOrigin(animatedSpriteData.origin);

	m_shadow = new Sprite();
	m_shadow->Init(shadowTexture);
	m_shadow->SetAlpha(0.7f);

	m_animator = new Animator();
	m_animator->Init(animatedSpriteData);
	m_animator->SetAnimation(0);
	
	std::vector<HitBoxData> hitboxData;
	hitboxData = GameDataManager::LoadHitboxData(data.name);

	m_hitBoxManager = new HitBoxManager();
	m_hitBoxManager->Init(this, hitboxData);
	
	m_movementSpeed = data.objectData.walkSpeed;
	m_acceleration = data.objectData.acceleration;
	m_deceleration = data.objectData.deceleration;

	m_startingState = startingState;
	m_stateMachine = new StateMachine<Enemy>(this);
	m_stateMachine->Init(EnemyIdleState::Instance(), nullptr, globalEnemyState);
	m_stateMachine->ChangeState(startingState);

	m_id = m_enemyData.objectData.id;
	m_health = m_enemyData.objectData.startingHealth;

	std::string enemyDataFile = "assets\\data\\damage\\" + data.type + "_damage.txt";

	if(!LoadDamageData(enemyDataFile))
	{
		std::string error = "Error! Enemy damage data " + enemyDataFile + " not found.";
		Logger::LogError(error);
	}

	m_dustFx = new SpriteFx();
	m_dustFx->Init("t_dust", "dustfx");

	m_vocalSoundSource = new SoundSource();
	m_vocalSoundSource->SetTarget(this);
	m_vocalSoundSource->SetLooping(false);
	m_vocalSoundSource->SetRelative(true);

	m_footStepsSoundSource = new SoundSource();
	m_footStepsSoundSource->SetTarget(this);
	m_footStepsSoundSource->SetLooping(true);
	m_footStepsSoundSource->SetRelative(true);

	m_punchSoundSource = new SoundSource();
	m_punchSoundSource->SetTarget(this);
	m_punchSoundSource->SetLooping(false);
	m_punchSoundSource->SetRelative(true);

	AudioEngine::Instance()->AddSoundSource(m_vocalSoundSource);
	AudioEngine::Instance()->AddSoundSource(m_footStepsSoundSource);
	AudioEngine::Instance()->AddSoundSource(m_punchSoundSource);

	ResetTimer(Randomiser::Instance()->GetRandNum(0.8f, 2.0f));

	m_active = false;
}

void Enemy::Update(float deltaTime)
{
	if(!m_active) return;

	m_stateMachine->Update();
	GameObject::Update(deltaTime);

	if(m_thinkingTimer > 0.0f) m_thinkingTimer -= deltaTime;
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
}

void Enemy::Render(Graphics* graphics)
{
	if(!m_active) return;

	if(m_shadow)
	{
		m_shadow->SetDepth(m_groundPosition.y / graphics->GetHeight() - 0.1f);
		m_shadow->Render(graphics);
	}

	if(m_spritesheet)
	{
		m_spritesheet->SetDepth(m_groundPosition.y / graphics->GetHeight());

		if(m_animator)
		{
			m_spritesheet->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation().from);
		}
		else
		{
			m_spritesheet->Render(graphics, 0);
		}
	}

	//	 render hitbox
	if(m_hitBoxManager)
		m_hitBoxManager->Render(graphics, m_camera);

	if(m_dustFx)
		m_dustFx->Render(graphics);
}

void Enemy::Reset()
{
	m_stateMachine->ChangeState(m_startingState);
	m_position = m_enemyData.objectData.startingPosition;
	m_grounded = true;
	m_movementSpeed = m_enemyData.objectData.walkSpeed;
	m_health = m_enemyData.objectData.startingHealth;
	ResetTimer(Randomiser::Instance()->GetRandNum(0.8f, 2.0f));
	m_active = false;
	m_dead = false;
	m_isFlashing = false;
}

void Enemy::Spawn(const Vector2& position)
{
	m_position = position;
	m_groundPosition = position;
	m_dead = false;
	m_active = true;
	m_isFlashing = false;
	m_health = m_enemyData.objectData.startingHealth;

	GetSprite()->EnableSprite();
	m_stateMachine->ChangeState(m_startingState);
}

void Enemy::SetData(const EnemyData& data)
{
	m_enemyData = data;
}

void Enemy::SetDead(bool isDead)
{
	m_dead = isDead;
}

void Enemy::SetPlayerTarget(Player* player)
{
	m_playerTarget = player;
}

void Enemy::SetHostile(bool isHostile)
{
	m_isHostile = isHostile;
}

void Enemy::ResetTimer(float timerMod)
{
	m_thinkingTimer = GetData().thinkingTime * timerMod;
}

void Enemy::ApplyDamage(GameObject* source, const int& amount)
{
	m_health -= amount;

	if(m_health < 0) m_health = 0;

	// true if health has gone or damage is high
	if(m_health < 1 || amount > 50)
	{
		// set knockback state
		m_stateMachine->ChangeState(EnemyKnockbackState::Instance());

		Vector2 direction = Vector2::Zero;

		// calculate direction to knockback
		if(this->GetPositionX() < source->GetPositionX())
		{
			direction = UnitVectors::UpLeft;
		}
		else
		{
			direction = UnitVectors::UpRight;
		}

		Knockback(direction, 100.0f);
		SetKnockbackCount(1);
	}
	else
	{
		m_stateMachine->ChangeState(EnemyHurtState::Instance());
	}

	PlayHurtSound();
}

void Enemy::Knockback(const Vector2& direction, const float& force)
{
	SetVelocity(direction);
	SetMovementSpeed(force);
}

void Enemy::Attack()
{
	int attackNum = Randomiser::Instance()->GetRandNum(1, 2);
	EnemyAttackState::Instance()->SetAttack(fmt::format("attack{}", attackNum));
	m_stateMachine->ChangeState(EnemyAttackState::Instance());
}

void Enemy::Kill()
{
	m_dead = true;
	m_deathTimer = EnemyDeadDuration;
}

void Enemy::ProcessSteering()
{
	m_targetVelocity = Vector2::Zero;
	m_targetVelocity += Seek() * 2;
	m_targetVelocity += Avoid();
	m_targetVelocity += Strafe();
	m_targetVelocity.Normalize();
}

void Enemy::Flash()
{
	if(!m_isFlashing) m_isFlashing = true;
}

Vector2 Enemy::Seek() const
{
	if(m_isHostile && NPCManager::Instance()->GetAttackingEnemy() != this) return Vector2::Zero;

	Vector2 direction = Vector2::Zero;
	Vector2 targetPosition = GetPlayerTarget()->GetPosition();
	Vector2 position = GetPosition();

	direction = targetPosition - position;

	if(direction.Length() < m_enemyData.attackRange)
		direction = -direction;

	direction.Normalize();

	return direction;
}

Vector2 Enemy::Avoid() const
{
	Vector2 force = Vector2::Zero;
	auto enemyList = m_npcManager->GetEnemyList();

	for(auto it = enemyList.begin(); it != enemyList.end(); it++)
	{
		if(*it == this || !(*it)->IsActive()) continue;

		auto toOther = m_position - (*it)->GetPosition();

		if(toOther.Length() > MinEnemyAvoidDistance) continue;

		toOther.Normalize();
		force += toOther / toOther.Length();
	}

	return force;
}

Vector2 Enemy::Strafe() const
{
	if(NPCManager::Instance()->GetAttackingEnemy() == this || !IsHostile()) return Vector2::Zero;

	auto toTarget = m_playerTarget->GetPosition() - GetPosition();
	auto crossProduct = Vector2(toTarget.y, -toTarget.x);
	crossProduct.Normalize();
	return crossProduct;
}

void Enemy::ShowEnemyHud()
{
	UIPortraitView* portraitView = static_cast<UIPortraitView*>(UIManager::GetView("Enemy Portrait"));

	if(portraitView)
	{
		portraitView->SetActive(true);
		portraitView->SetPortraitTexture(AssetLoader::GetTexture(fmt::format("t_{}_portrait", m_enemyData.type)));
	}

	UIBarView* healthbar = static_cast<UIBarView*>(UIManager::GetView("Enemy Health Bar"));

	if(healthbar)
	{
		healthbar->SetActive(true);
		healthbar->SetCurrentValue(m_health, true);
		healthbar->SetMaxValue(m_enemyData.objectData.startingHealth);
	}
}

void Enemy::PlayEntranceSound()
{
	uint32_t randomNumber = Randomiser::Instance()->GetRandNum(1, 4);

	std::wstring soundName = L"mook_entrance_00" + std::to_wstring(randomNumber);
	m_vocalSoundSource->SetSound(SoundManager::GetSound(soundName));
}

void Enemy::PlayWalkingSound()
{
	Sound* sound = SoundManager::GetSound(L"mook_walk");

	if(m_footStepsSoundSource->GetSound() != sound)
		m_footStepsSoundSource->SetSound(sound);
}

void Enemy::StopWalkingSound()
{
	m_footStepsSoundSource->SetSound(nullptr);
}

void Enemy::PlayPunchSound()
{
	Sound* sound = SoundManager::GetSound(L"mook_punch_001");
	
	float randomPitch = Randomiser::Instance()->GetRandNum(0.80f, 1.2f);
	m_punchSoundSource->SetPitch(randomPitch);
	m_punchSoundSource->SetSound(sound);
}

void Enemy::PlayHurtSound()
{
	uint32_t randomNumber = Randomiser::Instance()->GetRandNum(1, 4);

	std::wstring soundName = L"mook_hit_00" + std::to_wstring(randomNumber);
	m_vocalSoundSource->SetSound(SoundManager::GetSound(soundName));
}

void Enemy::PlayDeathSound()
{
	Sound* sound = SoundManager::GetSound(L"mook_death");

	if(m_vocalSoundSource->GetSound() != sound)
		m_vocalSoundSource->SetSound(sound);
}

DamageData Enemy::GetDamageData() const
{
	std::string stateName = m_stateMachine->GetCurrentState()->GetName();
	if(m_damageData.count(stateName) == 0)
		return DamageData();

	return m_damageData.at(stateName);
}