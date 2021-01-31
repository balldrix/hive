#include "Enemy.h"

#include "Graphics.h"
#include "Sprite.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "Resources.h"
#include "ControlSystem.h"
#include "pch.h"
#include "UnitVectors.h"
#include "Randomiser.h"
#include "InGameHudManager.h"
#include "BarController.h"
#include "Player.h"
#include "EnemyOwnedStates.h"
#include "StateMachine.h"
#include "Error.h"

Enemy::Enemy() :
	m_playerTarget(nullptr),
	m_stateMachine(nullptr),
	m_thinkingTimer(0.0f),
	m_isHostile(false),
	m_hudManager(nullptr),
	m_portraitSprite(nullptr),
	m_hitBoxSprite(nullptr),
	m_healthBar(nullptr)
{}


Enemy::~Enemy()
{
	ReleaseAll();
	DeleteAll();
}

void Enemy::Init(Graphics* graphics,
				 Camera* camera,
				 Player* player,
				 const EnemyData& data, 
				 Texture* spriteTexture, 
				 Texture* shadowTexture, 
				 Texture* hitBoxTexture, 
				 InGameHudManager* inGameUiManager, 
				 Sprite* portraitSprite,
				 State<Enemy>* globalEnemyState)
{
	m_camera = camera;
	m_playerTarget = player;
	m_enemyData = data;
	m_position = data.objectData.startingPosition;
	m_groundPosition = data.objectData.startingPosition;
	m_grounded = true;

	m_spriteSheet = new Spritesheet();
	m_spriteSheet->Init(spriteTexture, "GameData\\SpriteSheetData\\" + data.type + "SpritesheetData.json");
	
	m_shadow = new Sprite();
	m_shadow->Init(shadowTexture);
	m_shadow->SetAlpha(0.7f);
	
	m_animator = new Animator();
	m_animator->Init("GameData\\AnimationData\\" + data.type + "AnimationData.json");
	m_animator->SetAnimation(0);

	m_hitBoxSprite = new Sprite();
	m_hitBoxSprite->Init(hitBoxTexture);
	
	m_hitBoxManager = new HitBoxManager();
	m_hitBoxManager->Init(m_hitBoxSprite, "GameData\\HitBoxData\\" + data.type + "HitBoxData.json");
	m_hitBoxManager->SetCurrentHitBox(0);
	m_hitBoxManager->SetOwner(this);
	
	m_movementSpeed = data.objectData.walkSpeed;
	m_acceleration = data.objectData.acceleration;
	m_deceleration = data.objectData.deceleration;

	m_stateMachine = new StateMachine<Enemy>(this);
	m_stateMachine->Init(EnemyIdleState::Instance(), nullptr, globalEnemyState);

	m_id = m_enemyData.objectData.id;
	m_health = m_enemyData.objectData.startingHealth;

	m_hudManager = inGameUiManager;
	m_portraitSprite = portraitSprite;

	m_health = data.objectData.startingHealth;

	m_healthBar = new BarController();
	m_healthBar->Init(graphics);
	m_healthBar->SetMaxValue(m_health);
	m_healthBar->SetCurrentValue(m_health);
	m_healthBar->SetPosition(Vector2(InGameHudConstants::HealthBarPositionX, InGameHudConstants::EnemyHealthBarPositionY));

	float percentage = (float)m_health / (float)m_playerTarget->GetMaxHealth();
	unsigned int width = (unsigned int)(m_healthBar->GetWidth() * percentage);
	m_healthBar->SetWidth(width);

	std::string enemyDataFile = "GameData\\EnemyData\\Damage\\" + data.type + "Damage.txt";

	if(!LoadDamageData(enemyDataFile))
	{
		std::string error = "Error! Enemy damage data " + enemyDataFile + " not found.";
		Error::FileLog(error);
	}

	m_active = false;
}

void
Enemy::Update(float deltaTime)
{
	if(m_active == false)
		return;

	m_stateMachine->Update();
	GameObject::Update(deltaTime);
	m_thinkingTimer += deltaTime;
}

void
Enemy::Render(Graphics* graphics)
{
	if(m_active == false)
		return;

	if(m_shadow)
	{
		m_shadow->SetDepth(m_groundPosition.y / graphics->GetHeight());
		m_shadow->Render(graphics);
	}

	if(m_spriteSheet)
	{
		m_spriteSheet->SetDepth(m_groundPosition.y / graphics->GetHeight());

		if(m_animator)
		{
			m_spriteSheet->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation()->spritesheetIndex);
		}
		else
		{
			m_spriteSheet->Render(graphics, 0);
		}
	}

	// render hitbox
	//if(m_hitBoxManager)
		//m_hitBoxManager->Render(graphics);
}

void
Enemy::Reset()
{
	m_stateMachine->ChangeState(EnemyIdleState::Instance());
	m_position = m_enemyData.objectData.startingPosition;
	m_grounded = true;
	m_movementSpeed = m_enemyData.objectData.walkSpeed;
	m_hitBoxManager->SetCurrentHitBox(0);
	m_health = m_enemyData.objectData.startingHealth;
	m_thinkingTimer = 0.0f;
	m_active = false;
	m_dead = false;
}

void Enemy::SetData(const EnemyData& data)
{
	m_enemyData = data;
}

void Enemy::SetDead()
{
	m_dead = true;
}

void Enemy::SetPlayerTarget(Player* player)
{
	m_playerTarget = player;
}

void Enemy::SetHostile(bool isHostile)
{
	m_isHostile = isHostile;
}

void Enemy::ResetTimer()
{
	m_thinkingTimer = 0.0f;
}

void Enemy::ApplyDamage(GameObject* source, const int& amount)
{
	m_health -= amount;

	// true if health has gone or damage is high
	if(m_health < 1 || amount > 15)
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

		// knockback Enemy with force
		Knockback(direction, 100.0f);

		// bounce 
		SetKnockbackCount(2);
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
	int randomNum = Randomiser::Instance()->GetRandNum(0, 2);
	switch(randomNum)
	{
	case 0:
		EnemyAttackState::Instance()->SetAttack("Attack1");
		break;
	case 1:
		EnemyAttackState::Instance()->SetAttack("Attack2");
		break;
	case 2:
		EnemyAttackState::Instance()->SetAttack("Attack3");
		break;
	default:
		EnemyAttackState::Instance()->SetAttack("Attack1");
		break;
	}

	m_stateMachine->ChangeState(EnemyAttackState::Instance());
}

void Enemy::Kill()
{
	GetUiManager()->AddEnemyKill();
	GetUiManager()->HideEnemyHud(m_id);
	m_dead = true;
}

void Enemy::ShowEnemyHud()
{
	m_healthBar->SetCurrentValue(m_health);
	m_hudManager->ShowEnemyHud(m_id, m_portraitSprite, m_healthBar);
}

void Enemy::ReleaseAll()
{
	m_healthBar->ReleaseAll();
}

void Enemy::DeleteAll()
{
	if(m_healthBar)
	{
		delete m_healthBar;
		m_healthBar = nullptr;
	}

	if(m_stateMachine)
	{
		delete m_stateMachine;
		m_stateMachine = nullptr;
	}

	if(m_hitBoxManager)
	{
		delete m_hitBoxManager;
		m_hitBoxManager = nullptr;
	}	

	if(m_hitBoxSprite)
	{
		delete m_hitBoxSprite;
		m_hitBoxSprite = nullptr;
	}

	if(m_animator)
	{
		delete m_animator;
		m_animator = nullptr;
	}

	if(m_shadow)
	{
		delete m_shadow;
		m_shadow = nullptr;
	}

	if(m_spriteSheet)
	{
		delete m_spriteSheet;
		m_spriteSheet = nullptr;
	}
}

int Enemy::GetDamage() const
{
	std::string stateName = m_stateMachine->GetCurrentState()->GetName();
	if(m_damageData.count(stateName) == 0)
		return 0;

	return m_damageData.at(stateName);
}
