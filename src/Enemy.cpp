#include "Enemy.h"

#include "AnimatedSpriteData.h"
#include "Animator.h"
#include "AssetLoader.h"
#include "AudioEngine.h"
#include "Camera.h"
#include "CutsceneManager.h"
#include "DamageData.h"
#include "EnemyAttackState.h"
#include "EnemyDefinition.h"
#include "EnemyHurtState.h"
#include "EnemyIdleState.h"
#include "EnemyKnockbackState.h"
#include "EventManager.h"
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
#include <string>
#include <variant>
#include <vector>

using namespace GameplayConstants;

Enemy::Enemy() :
	m_playerTarget(nullptr),
	m_stateMachine(nullptr),
	m_portraitSprite(nullptr),
	m_hitBoxSprite(nullptr),
	m_vocalSoundSource(nullptr),
	m_footStepSoundSource(nullptr),
	m_attackSoundSource(nullptr),
	m_stateChangeTimer(0.0f),
	m_flashingTimer(0.0f),
	m_isFlashing(false),
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
	m_eventManager->UnRegisterEvent("PlaySound");

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
	delete m_hitBoxSprite;
	delete m_animator;
	delete m_eventManager;
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
	m_hitBoxSprite = nullptr;
	m_animator = nullptr;
	m_eventManager = nullptr;
	m_shadow = nullptr;
	m_spritesheet = nullptr;
}

void Enemy::Init(Camera* camera,
				Player* player,
				CutsceneManager* cutsceneManager,
				const EnemyDefinition& data,
				NPCManager* npcManager,
				Texture* shadowTexture,
				State<Enemy>* globalEnemyState,
				State<Enemy>* startingState)
{
	m_camera = camera;
	m_playerTarget = player;
	m_cutsceneManager = cutsceneManager;
	m_enemyDefinition = data;
	m_npcManager = npcManager;
	m_grounded = true;

	AnimatedSpriteData animatedSpriteData;
	animatedSpriteData = GameDataManager::LoadAnimatedSpriteData(data.spritesheetDataPath);

	m_spritesheet = new Spritesheet();
	m_spritesheet->Init(AssetLoader::GetTexture(data.textureId), animatedSpriteData.spriteFrameData);
	m_spritesheet->SetOrigin(m_enemyDefinition.spriteOrigin);

	m_shadow = new Sprite();
	m_shadow->Init(shadowTexture);
	m_shadow->SetAlpha(0.7f);

	m_eventManager = new EventManager();

	m_animator = new Animator();
	m_animator->Init(animatedSpriteData, m_eventManager);
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

	m_id = m_enemyDefinition.id;
	m_health = m_enemyDefinition.hp;

	m_dustFx = new SpriteFx();
	m_dustFx->Init("t_dust", "dustfx", Vector2(20.0f, 30.0f));

	m_vocalSoundSource = new SoundSource();
	m_vocalSoundSource->SetTarget(this);
	m_vocalSoundSource->SetLooping(false);
	m_vocalSoundSource->SetRelative(true);

	m_footStepSoundSource = new SoundSource();
	m_footStepSoundSource->SetTarget(this);
	m_footStepSoundSource->SetLooping(true);
	m_footStepSoundSource->SetRelative(true);

	m_attackSoundSource = new SoundSource();
	m_attackSoundSource->SetTarget(this);
	m_attackSoundSource->SetLooping(false);
	m_attackSoundSource->SetRelative(true);

	m_impactSoundSource = new SoundSource();
	m_impactSoundSource->SetTarget(this);
	m_impactSoundSource->SetLooping(false);
	m_impactSoundSource->SetRelative(true);

	AudioEngine::Instance()->AddSoundSource(m_vocalSoundSource, false);
	AudioEngine::Instance()->AddSoundSource(m_footStepSoundSource, false);
	AudioEngine::Instance()->AddSoundSource(m_attackSoundSource, true);
	AudioEngine::Instance()->AddSoundSource(m_impactSoundSource, false);

	m_impactSounds = {
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

	/*m_eventManager->RegisterEvent("PlaySound", [this](EventArgument arg)
	{
		if(!std::holds_alternative<std::string>(arg))
		{
			Logger::LogError("[Enemy] [RegisterEvents] Incorrect argument for PlaySound, must be a string");
			return true;
		}

		PlaySound(std::get<std::string>(arg));
		return true;
	});

	m_eventManager->RegisterEvent("MoveNPC", [this](EventArgument arg)
	{
		if(!std::holds_alternative<DirectX::XMFLOAT2>(arg))
		{
			Logger::LogError("[NPCManager] [RegisterEvent] Incorrect argument for MoveNPC, must be a Vector2");
			return true;
		}

		Vector2 position = std::get<DirectX::XMFLOAT2>(arg);
		return MoveNPC(position);
	});*/

	m_active = false;
}

void Enemy::Update(float deltaTime)
{
	if(!m_active) return;
	if(!m_cutsceneManager->IsActive()) m_stateMachine->Update();

	GameObject::Update(deltaTime);

	if(m_stateChangeTimer > 0.0f) m_stateChangeTimer -= deltaTime;
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
		m_shadow->SetDepth(m_groundPosition.y / graphics->GetBackbufferHeight() - 0.1f);
		m_shadow->Render(graphics);
	}

	if(m_spritesheet)
	{
		m_spritesheet->SetDepth(m_groundPosition.y / graphics->GetBackbufferHeight());

		if(m_animator)
		{
			m_spritesheet->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation().from);
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

void Enemy::Spawn(const Vector2& position)
{
	m_position = position;
	m_groundPosition = position;
	m_dead = false;
	m_active = true;
	m_isFlashing = false;
	m_health = m_enemyDefinition.hp;

	GetSprite()->EnableSprite();
	m_stateMachine->ChangeState(m_startingState);
}

void Enemy::SetDead(bool isDead)
{
	m_cutsceneManager->UnregisterEventManager(m_id);
	m_dead = isDead;
}

void Enemy::SetPlayerTarget(Player* player)
{
	m_playerTarget = player;
}

void Enemy::ResetStateChangeTimer()
{
	m_stateChangeTimer = Randomiser::Instance()->GetRandNumNormal(m_enemyDefinition.minStateChangeTime, m_enemyDefinition.maxStateChangeTime);
}

void Enemy::ApplyDamage(GameObject* source, const int& amount)
{
	m_health -= amount;

	if(m_health < 0) m_health = 0;

	PlayImpactSound();

	//@TODO add knockback, stun or juggle states
	if(m_health == 0)
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
}

void Enemy::Knockback(const Vector2& direction, const float& force)
{
	SetVelocity(direction);
	SetMovementSpeed(force);
}

void Enemy::Attack()
{
	int attackNum = Randomiser::Instance()->GetRandNumUniform(0, (int)m_enemyDefinition.damageData.size() - 1);
	EnemyAttackState::Instance()->SetAttack(m_enemyDefinition.damageData[attackNum].name);
	m_stateMachine->ChangeState(EnemyAttackState::Instance());
	NPCManager::Instance()->SetNextAttackingEnemy();
}

void Enemy::Kill()
{
	m_dead = true;
	m_deathTimer = EnemyDeadDuration;
}

void Enemy::ProcessSteering()
{
	m_targetVelocity = Vector2::Zero;
	m_targetVelocity += Seek() * 2.0f;
	m_targetVelocity += Avoid();
	m_targetVelocity.Normalize();
}

void Enemy::Flash()
{
	if(!m_isFlashing) m_isFlashing = true;
}

Vector2 Enemy::Seek() const
{
	Vector2 direction = Vector2::Zero;
	Vector2 targetPosition = GetPlayerTarget()->GetPosition();
	Vector2 position = GetPosition();

	direction = targetPosition - position;

	if(direction.Length() < m_enemyDefinition.attackRange)
		direction = -direction;

	direction.Normalize();

	return direction;
}

Vector2 Enemy::Avoid() const
{
	Vector2 force = Vector2::Zero;

	if(this == NPCManager::Instance()->GetAttackingEnemy()) return force;

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
	if(NPCManager::Instance()->GetAttackingEnemy() == this) return Vector2::Zero;

	auto toTarget = m_playerTarget->GetPosition() - GetPosition();
	auto crossProduct = Vector2(toTarget.y, -toTarget.x);
	crossProduct.Normalize();
	return crossProduct;
}

bool Enemy::MoveNPC(const Vector2& position)
{
	auto animationName = m_animator->GetAnimation().name;
	if((position - m_groundPosition).Length() < 1.0f) {
		m_currentVelocity = Vector2::Zero;
		if(animationName != "idle")
		{
			m_animator->SetAnimation("idle");
		}
		return true;
	}

	auto direction = position - m_groundPosition;
	direction.Normalize();
	m_targetVelocity = direction * m_movementSpeed;

	ApplyFacingDirection();

	if(animationName != "walk")
	{
		m_animator->SetAnimation("walk");
	}

	return false;
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

DamageData Enemy::GetDamageData() const
{
	std::string stateName = m_stateMachine->GetCurrentState()->GetName();
	
	for(const auto& data : m_enemyDefinition.damageData)
	{
		if(data.name == stateName) return data;
	}
	
	return DamageData();
}