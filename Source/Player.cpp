#include "Player.h"
#include "Graphics.h"
#include "Sprite.h"
#include "ControlSystem.h"
#include "SpriteSheet.h"
#include "Animator.h"
#include "HitBoxManager.h"
#include "Resources.h"
#include "ControlSystem.h"
#include "StateMachine.h"
#include "PlayerOwnedStates.h"

Player::Player() : m_stateMachine(nullptr)
{
}

Player::~Player()
{
	if(m_stateMachine)
	{
		delete m_stateMachine;
		m_stateMachine = nullptr;
	}
}

void Player::Init(const Vector2& position, SpriteSheet* sprite, Sprite* shadow, Animator* animator, HitBoxManager* hitBoxManager, ControlSystem* controlSystem)
{
	m_controlSystem = controlSystem;
	m_sprite = sprite;
	m_shadow = shadow;
	m_position = position;
	m_acceleration = PlayerAcceleration;
	m_deceleration = PlayerDeceleration;
	m_movementSpeed = WalkSpeed;
	m_animator = animator;
	m_animator->SetAnimation(0);
	m_hitBoxManager = hitBoxManager;

	m_stateMachine = new StateMachine<Player>(this);
	m_stateMachine->Init(PlayerIdleState::Instance(), nullptr, PlayerGlobalState::Instance());
}

void Player::Update(float deltaTime)
{
	// update player state machine
	m_stateMachine->Update();

	// update object
	GameObject::Update(deltaTime);

	if(m_stateMachine->GetCurrentState() != PlayerAttackState::Instance())
	{
		m_controlSystem->Update(deltaTime);
	}
}

void Player::Render(Graphics* graphics)
{
	// render shadow first
	if(m_shadow)
	{
		m_shadow->SetDepth(m_groundPosition.y / graphics->GetHeight());
		m_shadow->Render(graphics);
	}

	if(m_sprite)
	{
		// set layer depth
		m_sprite->SetDepth(m_groundPosition.y / graphics->GetHeight());

		// render player sprite
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

void Player::Reset()
{
	// set player state back to Idle
	m_stateMachine->ChangeState((PlayerIdleState::Instance()));

	// Set Position 
	// TODO set world position and screen position
	SetPosition(PlayerStartScreenPositionX, PlayerStartScreenPositionY);

	// reset hitboxes
	m_hitBoxManager->SetCurrentHitBox(0);

	SetActive(true);
}

void Player::Move(const Vector2 & direction)
{
	// true if switching direction
	if(direction.x < 0 && m_currentVelocity.x > 0 ||
		direction.x > 0 && m_currentVelocity.x < 0)
	{
		// slow down before switching
		SetTargetVelocityX(0.0f);
		return;
	}

	SetTargetVelocity(direction);

	// true if moving to the left
	if(m_currentVelocity.x < 0)
	{
		FlipHorizontally(true);
	}

	// true if moving to the right
	if(m_currentVelocity.x > 0)
	{
		FlipHorizontally(false);
	}
}

// stop velocity
void Player::Stop()
{
	SetTargetVelocity(Vector2::Zero);
	SetCurrentVelocity(Vector2::Zero);
}

// normal attack behaviour
void Player::Attack()
{
	if(m_animator->GetAnimation()->name == "Idle" || m_animator->GetAnimation()->name == "Walking")
	{
		// use combo counter to get the correct attack 
		switch(m_controlSystem->GetComboCounter())
			{
			case 0:
			case 1:
				PlayerAttackState::Instance()->SetAttack("Attack 1");
				break;
			case 2:
				PlayerAttackState::Instance()->SetAttack("Attack 2");
				break;
			case 3:
				PlayerAttackState::Instance()->SetAttack("Attack 3");
				break;
			default:
				PlayerAttackState::Instance()->SetAttack("Attack 1");
				break;
		}

		m_stateMachine->ChangeState((PlayerAttackState::Instance()));
		m_controlSystem->SetInput(Controls::None);
	}
}

