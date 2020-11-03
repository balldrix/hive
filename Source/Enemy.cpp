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

Enemy::Enemy() :
	m_playerTarget(nullptr),
	m_stateMachine(nullptr),
	m_thinkingTimer(0.0f),
	m_isHostile(false),
	m_uiManager(nullptr),
	m_portraitSprite(nullptr),
	m_healthBar(nullptr)
{}

Enemy::~Enemy()
{
	ReleaseAll();
	DeleteAll();
}

void Enemy::Init(Graphics* graphics, const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, InGameHudManager* inGameUiManager, Sprite* portraitSprite)
{
	m_position = position;
	m_sprite = new SpriteSheet(*sprite);
	m_shadow = new Sprite(*shadow);
	m_animator = new Animator(*animator);
	m_animator->SetAnimation(0);
	m_hitBoxManager = new HitBoxManager(*hitBoxManager);
	m_hitBoxManager->SetCurrentHitBox(0);
	
	ObjectData data = m_enemyData.objectData;
	m_movementSpeed = data.walkSpeed;
	m_acceleration = data.acceleration;
	m_deceleration = data.deceleration;

	m_stateMachine = new StateMachine<Enemy>(this);
	m_stateMachine->Init(EnemyIdleState::Instance(), nullptr, EnemyGlobalState::Instance());

	m_id = m_enemyData.objectData.id;
	m_health = m_enemyData.objectData.startingHealth;

	m_uiManager = inGameUiManager;
	m_portraitSprite = portraitSprite;

	m_healthBar = new BarController();
	m_healthBar->Init(graphics);
	m_healthBar->SetMaxValue(m_health);
	m_healthBar->SetCurrentValue(m_health);
	m_healthBar->SetPosition(Vector2(InGameHudConstants::HealthBarPositionX, InGameHudConstants::EnemyHealthBarPositionY));

	float percentage = (float)m_health / (float)m_playerTarget->GetMaxHealth();
	unsigned int width = (float)m_healthBar->GetWidth() * percentage;
	m_healthBar->SetWidth(width);
}

void
Enemy::Update(float deltaTime)
{
	// update state machine
	m_stateMachine->Update();

	// update object
	GameObject::Update(deltaTime);

	m_thinkingTimer += deltaTime;
}

void
Enemy::Render(Graphics* graphics)
{
	// render shadow first
	if(m_shadow)
	{
		m_shadow->SetDepth(m_groundPosition.y / graphics->GetHeight());
		m_shadow->Render(graphics);
	}

	if(m_sprite)
	{
		m_sprite->SetDepth(m_groundPosition.y / graphics->GetHeight());

		// render enemy sprite
		if(m_animator)
		{
			m_sprite->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation()->spriteSheetIndex);
		}
		else
		{
			m_sprite->Render(graphics, 0);
		}
	}

	// render hitbox
	//if(m_hitBoxManager)
	//{
	//	m_hitBoxManager->Render(graphics);
	//}
}

void
Enemy::Reset()
{
	// set enemy state back to Idle
	m_stateMachine->ChangeState(EnemyIdleState::Instance());

	// Set Position 
	m_position = m_enemyData.objectData.startingPosition;
	m_grounded = true;
	m_movementSpeed = m_enemyData.objectData.walkSpeed;

	// reset hitboxes
	m_hitBoxManager->SetCurrentHitBox(0);

	SetActive(true);
	m_health = m_enemyData.objectData.startingHealth;
	m_thinkingTimer = 0.0f;
}

void Enemy::SetData(const EnemyData& data)
{
	m_enemyData = data;
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
		Knockback(direction, 80.0f);

		// bounce 
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

	m_stateMachine->ChangeState((EnemyAttackState::Instance()));
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
	m_uiManager->ShowEnemyHud(m_id, m_portraitSprite, m_healthBar);
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

	if(m_sprite)
	{
		delete m_sprite;
		m_sprite = nullptr;
	}

	if(m_shadow)
	{
		delete m_shadow;
		m_shadow = nullptr;
	}

	if(m_animator)
	{
		delete m_animator;
		m_animator = nullptr;
	}

	if(m_stateMachine)
	{
		delete m_stateMachine;
		m_stateMachine = nullptr;
	}
}

int Enemy::GetDamage() const
{
	std::string stateName = m_stateMachine->GetCurrentState()->GetName();
	if(m_damageData.count(stateName) == 0)
		return 0;

	return m_damageData.at(stateName);
}
