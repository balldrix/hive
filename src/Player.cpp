#include "Player.h"

#include "AnimatedSpriteData.h"
#include "AnimationEventManager.h"
#include "Animator.h"
#include "AssetLoader.h"
#include "AudioEngine.h"
#include "Camera.h"
#include "ControlSystem.h"
#include "DamageData.h"
#include "GameDataManager.h"
#include "GameObject.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "HitBoxManager.h"
#include "LevelCollision.h"
#include "Logger.h"
#include "PlayerAttackState.h"
#include "PlayerBlockState.h"
#include "PlayerConstants.h"
#include "PlayerDeadState.h"
#include "PlayerGlobalState.h"
#include "PlayerHurtState.h"
#include "PlayerIdleState.h"
#include "PlayerKnockbackState.h"
#include "Randomiser.h"
#include "Sound.h"
#include "SoundManager.h"
#include "SoundSource.h"
#include "Sprite.h"
#include "SpriteFx.h"
#include "Spritesheet.h"
#include "StateMachine.h"
#include "UIBarView.h"
#include "UIKillCount.h"
#include "UIKillMilestoneView.h"
#include "UIManager.h"
#include "UnitVectors.h"

#include <cstdint>
#include <directxtk/SimpleMath.h>
#include <fstream>
#include <iosfwd>
#include <string>
#include <system_error>
#include <functional>
#include <variant>

using namespace PlayerConstants;
using namespace GlobalConstants;

Player::Player() :
	m_stateMachine(nullptr),
	m_knockoutTimer(0.0f),
	m_punchSoundSource(nullptr),
	m_footStepsSoundSource(nullptr),
	m_vocalSoundSource(nullptr),
	m_recentFootstepFrame(0),
	m_hurtTimer(0.0f),
	m_kills(0),
	m_special(100)
{
}

Player::~Player()
{
	AnimationEventManager::UnRegisterEvent("MovePlayer");

	AudioEngine::Instance()->RemoveSoundSource(m_vocalSoundSource);
	AudioEngine::Instance()->RemoveSoundSource(m_footStepsSoundSource);
	AudioEngine::Instance()->RemoveSoundSource(m_punchSoundSource);

	delete m_vocalSoundSource;
	delete m_footStepsSoundSource;
	delete m_punchSoundSource;
	delete m_dustFx;
	delete m_stateMachine;
	delete m_spritesheet;

	m_vocalSoundSource = nullptr;
	m_footStepsSoundSource = nullptr;
	m_punchSoundSource = nullptr;
	m_dustFx = nullptr;
	m_stateMachine = nullptr;
	m_spritesheet = nullptr;
}

void Player::Init(ControlSystem* controlSystem)
{
	Logger::LogInfo("Initialising Player.");

	m_controlSystem = controlSystem;

	m_playerDefinition = LoadPlayerDefinition();

	AnimatedSpriteData animatedSpriteData;
	animatedSpriteData = GameDataManager::LoadAnimatedSpriteData(m_playerDefinition.spritesheetDataPath);

	m_spritesheet = new Spritesheet();
	m_spritesheet->Init(AssetLoader::GetTexture(m_playerDefinition.textureId), animatedSpriteData.spriteFrameData);
	m_spritesheet->SetOrigin(m_playerDefinition.spriteOrigin);

	m_shadow = new Sprite();
	m_shadow->Init(AssetLoader::GetTexture(m_playerDefinition.shadowId));
	m_shadow->SetAlpha(0.7f);

	m_animator = new Animator();
	m_animator->Init(animatedSpriteData);
	m_animator->SetAnimation(0);

	m_hitBoxManager = new HitBoxManager();
	m_hitBoxManager->Init(this, GameDataManager::LoadHitboxData(m_playerDefinition.hitBoxDataPath));

	m_position.x = StartingPositionX;
	m_position.y = StartingPositionY;
	m_groundPosition = m_position;
	m_acceleration = m_playerDefinition.acceleration;
	m_deceleration = m_playerDefinition.deceleration;
	m_movementSpeed = m_playerDefinition.walkSpeed;
	m_grounded = false;

	m_stateMachine = new StateMachine<Player>(this);
	m_stateMachine->Init(PlayerIdleState::Instance(), nullptr, PlayerGlobalState::Instance());

	m_dustFx = new SpriteFx();
	m_dustFx->Init("t_dust", "dustfx", Vector2(20.0f, 30.0f));

	m_health = m_playerDefinition.hp;

	m_punchSoundSource = new SoundSource();
	m_punchSoundSource->SetTarget(this);
	m_punchSoundSource->SetLooping(false);
	m_punchSoundSource->SetRelative(true);

	m_footStepsSoundSource = new SoundSource();
	m_footStepsSoundSource->SetTarget(this);
	m_footStepsSoundSource->SetLooping(false);
	m_footStepsSoundSource->SetRelative(true);

	m_vocalSoundSource = new SoundSource();
	m_vocalSoundSource->SetTarget(this);
	m_vocalSoundSource->SetLooping(false);
	m_vocalSoundSource->SetRelative(true);

	AudioEngine::Instance()->SetListener(this);
	AudioEngine::Instance()->AddSoundSource(m_punchSoundSource);
	AudioEngine::Instance()->AddSoundSource(m_footStepsSoundSource);
	AudioEngine::Instance()->AddSoundSource(m_vocalSoundSource);

	m_playerSounds =
	{
		{ "Attack1",	L"punch_001" },
		{ "Attack2",	L"punch_003" },
		{ "Attack3",	L"punch_004" },
		{ "Walking1",	L"walk_001"},
		{ "Walking2",	L"walk_002"},
		{ "Walking3",	L"walk_003"},
		{ "Walking4",	L"walk_004"},
		{ "Hurt1",		L"hit_001"},
		{ "Hurt2",		L"hit_002"},
		{ "Hurt3",		L"hit_003"},
		{ "Dead",		L"scream"}
	};

	InitStats();
	RegisterAnimationEvents();
}

void Player::Update(float deltaTime)
{
	if(m_dead == true)
		return;

	m_stateMachine->Update();
	GameObject::Update(deltaTime);

	m_hitBoxManager->Update(m_animator->GetCurrentFrame());

	if(m_stateMachine->IsInState(*PlayerDeadState::Instance()) && m_health <= 0)
		m_deathTimer += deltaTime;

	if(m_deathTimer > m_playerDefinition.deathTime)
		Kill();

	if(m_stateMachine->IsInState(*PlayerHurtState::Instance()))
	{
		m_hurtTimer += deltaTime;
	}

	if(m_stateMachine->IsInState(*PlayerDeadState::Instance()) && m_health > 0)
		m_knockoutTimer += deltaTime;

	if(m_knockoutTimer > m_playerDefinition.knockoutDuration)
		m_stateMachine->ChangeState(PlayerIdleState::Instance());

	if(!m_controlSystem->CanAttack())
		return;

	if(m_controlSystem->GetLastKeyPressed() == Controls::NormalAttack)
	{
		NormalAttack();
	}

	if(m_controlSystem->GetLastKeyPressed() == Controls::StrongAttack)
	{
		StrongAttack();
	}

	if(m_controlSystem->GetLastKeyPressed() == Controls::SpecialAttack)
	{
		SpecialAttack();
	}

	if(m_health < 10)
	{
		IncreaseSpecial(CriticalHealthSpecialRate * deltaTime);
	}

	UpdateStats();
}

void Player::Kill()
{
	m_dead = true;
}

void Player::Respawn()
{
	m_stateMachine->ChangeState((PlayerIdleState::Instance()));
	m_position = m_camera->GetPosition() + Vector2(GameWidth * 0.5f, StartingPositionY);
	m_groundPosition = m_position;
	m_position.y = StartingPositionY;
	m_deathTimer = 0.0f;
	m_knockoutTimer = 0.0f;
	m_dead = false;
	m_active = true;
	m_grounded = false;
	m_health = m_playerDefinition.hp;
	m_special = 0;
	SetVelocity(m_currentVelocity.x, m_currentVelocity.y + FallingSpeed);

	UIKillCount* killCount = static_cast<UIKillCount*>(UIManager::GetView("Player Kill Count"));

	if(killCount)
		killCount->SetValue(m_kills);
}

void Player::ResetKnockoutTimer()
{
	m_knockoutTimer = 0.0f;
}

void Player::AddKill()
{
	m_kills++;

	UIKillCount* killCount = static_cast<UIKillCount*>(UIManager::GetView("Player Kill Count"));

	if(killCount)
		killCount->UpdateKills(m_kills);

	if(m_kills % 100 != 0)
		return;

	UIKillMilestoneView* milestoneView = static_cast<UIKillMilestoneView*>(UIManager::GetView("Kill Milestone"));

	if(milestoneView)
		milestoneView->SetValue(m_kills);
}

void Player::IncreaseSpecial(float value)
{
	m_special += value;

	if(m_special > MaxSpecial) m_special = MaxSpecial;
}

void Player::Render(Graphics* graphics)
{
	if(m_spritesheet)
	{
		// set layer depth
		m_spritesheet->SetDepth(m_groundPosition.y / graphics->GetHeight());

		// render player sprite
		if(m_animator)
		{
			m_spritesheet->Render(graphics, m_animator->GetCurrentFrame() + m_animator->GetAnimation().from);
		}
		else
		{
			m_spritesheet->Render(graphics, 0);
		}
	}

	if(m_shadow)
	{
		m_shadow->SetDepth(m_groundPosition.y / graphics->GetHeight() - 0.1f);
		m_shadow->Render(graphics);
	}

	// render hitbox
	if(m_hitBoxManager)
		m_hitBoxManager->Render(graphics, m_camera);

	if(m_dustFx)
		m_dustFx->Render(graphics);
}

void Player::Reset()
{
	m_stateMachine->ChangeState((PlayerIdleState::Instance()));
	SetPosition(StartingPositionX, StartingPositionY);
	m_groundPosition = m_position;
	m_position.y = StartingPositionY;
	m_grounded = false;
	m_health = m_playerDefinition.hp;
	m_deathTimer = 0.0f;
	m_dead = false;
	m_active = true;
	m_kills = 0;
	m_special = 100;
	SetVelocity(Vector2::Zero);
}

DamageData Player::GetDamageData() const
{
	std::string stateName = m_stateMachine->GetCurrentState()->GetName();

	for(const auto& data : m_playerDefinition.damageData)
	{
		if(data.name == stateName) return data;
	}

	return DamageData();
}

void Player::Move(const Vector2& direction)
{
	if(m_stateMachine->IsInState(*PlayerBlockState::Instance()) == true)
		return;

	if(direction.x < 0 && m_currentVelocity.x > 0 ||
		direction.x > 0 && m_currentVelocity.x < 0)
	{
		SetTargetVelocityX(0.0f);
		return;
	}

	SetTargetVelocity(direction);
}

void Player::Run()
{
	if(m_stateMachine->IsInState(*PlayerBlockState::Instance()) == true)
		return;

	m_movementSpeed = m_playerDefinition.runningSpeed;
}

void Player::Walk()
{
	if(m_stateMachine->IsInState(*PlayerBlockState::Instance()) == true)
		return;

	m_movementSpeed = m_playerDefinition.walkSpeed;
}

void Player::Stop()
{
	SetTargetVelocity(Vector2::Zero);
	SetCurrentVelocity(Vector2::Zero);
}

void Player::Block()
{
	if(m_stateMachine->IsInState(*PlayerBlockState::Instance()))
		return;

	m_stateMachine->ChangeState(PlayerBlockState::Instance());
}

void Player::ApplyDamage(GameObject* source, const int& amount)
{
	PlayHurtSound();

	if(m_stateMachine->IsInState(*PlayerBlockState::Instance()))
	{
		m_health -= 1;
		return;
	}

	m_health -= amount;

	if(m_health < 1 || amount > 15)
	{
		m_stateMachine->ChangeState(PlayerKnockbackState::Instance());

		Vector2 direction = Vector2::Zero;

		if(this->GetPositionX() < source->GetPositionX())
		{
			direction = UnitVectors::UpLeft;
		}
		else
		{
			direction = UnitVectors::UpRight;
		}

		Knockback(direction, 80.0f);
		SetKnockbackCount(2);
	}
	else
	{
		m_stateMachine->ChangeState(PlayerHurtState::Instance());
	}

	auto flash = UIManager::GetView("UI Screen Flash FX");
	if(flash) flash->TransitionIn(true);
}

void Player::Knockback(const Vector2& direction, const float& force)
{
	SetVelocity(direction);
	SetMovementSpeed(force);
}

void Player::PlayPunchSound(const std::string& name)
{
	std::wstring soundName = m_playerSounds[name];
	m_punchSoundSource->SetSound(SoundManager::GetSound(soundName));
}

void Player::PlayWalkingSound()
{
	if(m_recentFootstepFrame == m_animator->GetCurrentFrame())
		return;

	m_recentFootstepFrame = m_animator->GetCurrentFrame();

	uint32_t randomWalkIndex = Randomiser::Instance()->GetRandNum(1, 4);

	std::wstring soundName = m_playerSounds[m_stateMachine->GetCurrentState()->GetName() + std::to_string(randomWalkIndex)];
	m_footStepsSoundSource->SetSound(SoundManager::GetSound(soundName));
}

void Player::PlayHurtSound()
{
	uint32_t randomHurtSound = Randomiser::Instance()->GetRandNum(1, 3);

	std::wstring soundName = m_playerSounds[m_stateMachine->GetCurrentState()->GetName() + std::to_string(randomHurtSound)];
	m_vocalSoundSource->SetSound(SoundManager::GetSound(soundName));
}

void Player::PlayDeathSound()
{
	std::wstring soundName = m_playerSounds[m_stateMachine->GetCurrentState()->GetName()];

	Sound* sound = SoundManager::GetSound(soundName);

	if(m_vocalSoundSource->GetSound() != sound)
		m_vocalSoundSource->SetSound(sound);
}

PlayerDefinition Player::LoadPlayerDefinition()
{
	Logger::LogInfo("Loading Player definition.");

	auto path = "assets\\data\\player\\playerDefinition.json";
	std::ifstream file;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(path);
	}
	catch(std::system_error& e)
	{
		std::string message = fmt::format("[Player] [LoadPlayerDefinition] Failed to load Player Definition data at {0}: {1}.",
			path,
			e.code().message());

		Logger::LogError(message);
		return PlayerDefinition();
	}

	json j = json::parse(file);
	return j.get<PlayerDefinition>();
}

void Player::NormalAttack()
{
	if(m_controlSystem->GetComboCounter() == MaxCombo)
	{
		m_controlSystem->ResetComboCount();
	}

	Attack("attackNormal_");
}

void Player::StrongAttack()
{
	Attack("attackStrong_");
	m_controlSystem->ResetComboCount();
}

void Player::SpecialAttack()
{
	m_special = 0;
	m_controlSystem->SetControlsPressed(Controls::None);
	PlayerAttackState::Instance()->SetAttack("special");
	m_stateMachine->ChangeState(PlayerAttackState::Instance());
	m_controlSystem->ResetComboCount();

	auto flash = UIManager::GetView("UI Screen Flash FX");
	if(flash) flash->TransitionIn(true);
}

void Player::Attack(std::string attackName)
{
	m_controlSystem->SetControlsPressed(Controls::None);

	auto comboCounter = m_controlSystem->GetComboCounter();
	attackName.append(std::to_string(comboCounter + 1));

	PlayerAttackState::Instance()->SetAttack(attackName);
	m_stateMachine->ChangeState(PlayerAttackState::Instance());
}

void Player::InitStats()
{
	UIBarView* healthbar = static_cast<UIBarView*>(UIManager::GetView("Player Health Bar"));

	if(healthbar)
	{
		healthbar->SetMaxValue(m_playerDefinition.hp);
		healthbar->SetCurrentValue(m_health);
	}

	UIBarView* specialbar = static_cast<UIBarView*>(UIManager::GetView("Player Special Bar"));

	if(specialbar)
	{
		specialbar->SetMaxValue(MaxSpecial);
		specialbar->SetCurrentValue((int)m_special);
	}
}

void Player::UpdateStats()
{
	UIBarView* healthbar = static_cast<UIBarView*>(UIManager::GetView("Player Health Bar"));

	if(healthbar)
	{
		healthbar->SetMaxValue(m_playerDefinition.hp);
		healthbar->SetCurrentValue(m_health, true);
	}

	UIBarView* specialbar = static_cast<UIBarView*>(UIManager::GetView("Player Special Bar"));

	if(specialbar)
	{
		specialbar->SetMaxValue(MaxSpecial);
		specialbar->SetCurrentValue((int)m_special, true);
	}
}

void Player::RegisterAnimationEvents()
{
	AnimationEventManager::RegisterEvent("MovePlayer", [this](EventArgument arg) {
		if(!std::holds_alternative<float>(arg))
		{
			Logger::LogError("[Player] [RegisterEvents] Incorrect argument for MovePlayer, must be a float");
			return;
		}

		MovePlayerEvent(std::get<float>(arg));
	});
}

void Player::MovePlayerEvent(float distance)
{
	Vector2 offset = m_facingDirection == Vector3::Right ? Vector2(distance, 0.0f) : Vector2(-distance, 0.0f);
	Vector2 newPosition = m_position += offset;
	Vector2 newGroundPosition = m_groundPosition += offset;
	if(LevelCollision::IsCollision(newPosition) || LevelCollision::IsCollision(newGroundPosition)) return;

	m_position = newPosition;
	m_groundPosition = newGroundPosition;
}
