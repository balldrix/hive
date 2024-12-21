#include "GameplayGameState.h"

#include "AABB.h"
#include "Animator.h"
#include "AudioEngine.h"
#include "Camera.h"
#include "ControlSystem.h"
#include "EncounterHandler.h"
#include "EncounterSceneState.h"
#include "Enemy.h"
#include "GameplayConstants.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "GlobalConstants.h"
#include "Graphics.h"
#include "HitBoxManager.h"
#include "ImpactFx.h"
#include "Input.h"
#include "LevelRenderer.h"
#include "Logger.h"
#include "NPCManager.h"
#include "ParticleSystem.h"
#include "Player.h"
#include "PlayerBlockState.h"
#include "PlayerDeadState.h"
#include "PlayerHurtState.h"
#include "PlayerIdleState.h"
#include "PlayerKnockbackState.h"
#include "Randomiser.h"
#include "SoundSource.h"
#include "SpriteSheet.h"
#include "StateMachine.h"
#include "Timer.h"
#include "TravellingHandler.h"
#include "TravellingSceneState.h"
#include "UIManager.h"
#include "UnitVectors.h"

#include <cmath>
#include <DirectXColors.h>
#include <directxtk/SimpleMath.h>
#include <fmt/core.h>
#include <vector>
#include <WinUser.h>

using namespace GlobalConstants;
using namespace GameplayConstants;

GameplayGameState::GameplayGameState() :
	m_graphics(nullptr),
	m_input(nullptr),
	m_camera(nullptr),
	m_controlSystem(nullptr),
	m_NPCManager(nullptr),
	m_player(nullptr),
	m_levelRenderer(nullptr),
	m_sceneStateMachine(nullptr),
	m_encounterHandler(nullptr),
	m_travellingHandler(nullptr),
	m_musicSoundSource(nullptr),
	m_canAttack(true),
	m_running(false),
	m_playerBoundary(AABB()),
	m_deltaTime(0.0f),
	m_stopTimer(0.0f),
	m_displayHitBoxes(false),
	m_impactFxSpritesheet(nullptr),
	m_impactFxAnimator(nullptr),
	m_impactFx(nullptr),
	m_particleSystem(nullptr),
	m_collisionCooldown(0.0f),
	m_isCollisionOnCooldown(false),
	GameState("Gameplay")
{}

GameplayGameState::GameplayGameState(GameStateManager* gameStateManager) : GameplayGameState()
{
	m_gameStateManager = gameStateManager;
	m_graphics = m_gameStateManager->GetGraphics();
	m_input = m_gameStateManager->GetInput();
}

GameplayGameState::~GameplayGameState()
{
	DeleteAssets();
}

void GameplayGameState::OnEntry()
{
}

void GameplayGameState::OnExit()
{
}

void GameplayGameState::LoadAssets()
{
	Timer timer;
	unsigned __int64 startTime = timer.GetTicks();

	//SoundManager::AddSound(L"assets\\sounds\\punch_001.wav");
	//SoundManager::AddSound(L"assets\\sounds\\punch_003.wav");
	//SoundManager::AddSound(L"assets\\sounds\\punch_004.wav");
	//SoundManager::AddSound(L"assets\\sounds\\walk_001.wav");
	//SoundManager::AddSound(L"assets\\sounds\\walk_002.wav");
	//SoundManager::AddSound(L"assets\\sounds\\walk_003.wav");
	//SoundManager::AddSound(L"assets\\sounds\\walk_004.wav");
	//SoundManager::AddSound(L"assets\\sounds\\hit_001.wav");
	//SoundManager::AddSound(L"assets\\sounds\\hit_002.wav");
	//SoundManager::AddSound(L"assets\\sounds\\hit_003.wav");
	//SoundManager::AddSound(L"assets\\sounds\\scream.ogg");
	//SoundManager::AddSound(L"assets\\sounds\\mook_entrance_001.wav");
	//SoundManager::AddSound(L"assets\\sounds\\mook_entrance_002.wav");
	//SoundManager::AddSound(L"assets\\sounds\\mook_entrance_003.wav");
	//SoundManager::AddSound(L"assets\\sounds\\mook_entrance_004.wav");
	//SoundManager::AddSound(L"assets\\sounds\\mook_walk.wav");
	//SoundManager::AddSound(L"assets\\sounds\\mook_punch_001.wav");
	//SoundManager::AddSound(L"assets\\sounds\\mook_hit_001.wav");
	//SoundManager::AddSound(L"assets\\sounds\\mook_hit_002.wav");
	//SoundManager::AddSound(L"assets\\sounds\\mook_hit_003.wav");
	//SoundManager::AddSound(L"assets\\sounds\\mook_hit_004.wav");
	//SoundManager::AddSound(L"assets\\sounds\\mook_death.wav");
	//SoundManager::AddSound(L"assets\\sounds\\boss_entrance_001.wav");
	//SoundManager::AddSound(L"assets\\sounds\\boss_walk_001.wav");
	//SoundManager::AddSound(L"assets\\sounds\\boss_walk_002.wav");
	//SoundManager::AddSound(L"assets\\sounds\\boss_walk_003.wav");
	//SoundManager::AddSound(L"assets\\sounds\\boss_punch_001.wav");
	//SoundManager::AddSound(L"assets\\sounds\\boss_punch_002.wav");
	//SoundManager::AddSound(L"assets\\sounds\\boss_punch_003.wav");
	//SoundManager::AddSound(L"assets\\sounds\\boss_punch_004.wav");
	//SoundManager::AddSound(L"assets\\sounds\\travelling_master.wav");

	m_camera = new Camera();
	m_controlSystem = new ControlSystem();
	m_NPCManager = new NPCManager();
	m_player = new Player();
	m_levelRenderer = new LevelRenderer();
	m_sceneStateMachine = new StateMachine<GameplayGameState>(this);
	m_encounterHandler = new EncounterHandler();
	m_travellingHandler = new TravellingHandler();

	m_player->Init(m_controlSystem);
	m_player->SetCamera(m_camera);
	m_camera->SetTarget(m_player);

	m_levelRenderer->Init(m_graphics, m_camera);
	m_NPCManager->Init(m_graphics, m_camera, m_player);
	
	m_sceneStateMachine->Init(TravellingSceneState::Instance(), nullptr, nullptr);
	m_encounterHandler->Init(m_NPCManager->GetEnemyList());

	m_playerBoundary.SetMin(Vector2(StartingBoundaryMinX, StartingBoundaryMinY));
	m_playerBoundary.SetMax(Vector2((float)m_levelRenderer->GetLevelPixelWidth() - 1.0f, StartingBoundaryMaxY));
	
	m_camera->Init(GameWidth);
	
	m_musicSoundSource = new SoundSource();
	m_musicSoundSource->SetTarget(m_player);
	m_musicSoundSource->SetLooping(true);
	m_musicSoundSource->SetRelative(true);

	m_impactFx = new ImpactFx();
	m_impactFx->Init();

	m_particleSystem = new ParticleSystem();
	m_particleSystem->Init(m_graphics);

	/*AudioEngine::Instance()->AddSoundSource(m_musicSoundSource);

	const std::wstring musicTitle = L"travelling_master";
	m_musicSoundSource->SetSound(SoundManager::GetSound(musicTitle));*/

	m_running = true;

	unsigned __int64 endTime = timer.GetTicks();
	unsigned __int64 timeDiff = endTime - startTime;
	float loadingDuration = (float)timeDiff / (float)timer.GetFrequency();

	Logger::LogInfo(fmt::format("Gameplay Loading took {}s", loadingDuration));
}

void GameplayGameState::DeleteAssets()
{
	delete m_particleSystem;
	m_particleSystem = nullptr;

	delete m_impactFx;
	m_impactFx = nullptr;

	delete m_impactFxAnimator;
	m_impactFxAnimator = nullptr;

	delete m_impactFxSpritesheet;
	m_impactFxSpritesheet = nullptr;

	AudioEngine::Instance()->RemoveSoundSource(m_musicSoundSource);

	delete m_musicSoundSource;
	m_musicSoundSource = nullptr;

	delete m_travellingHandler;
	m_travellingHandler = nullptr;

	delete m_encounterHandler;
	m_encounterHandler = nullptr;

	delete m_sceneStateMachine;
	m_sceneStateMachine = nullptr;

	delete m_levelRenderer;
	m_levelRenderer = nullptr;

	delete m_player;
	m_player = nullptr;

	delete m_NPCManager;
	m_NPCManager = nullptr;

	delete m_controlSystem;
	m_controlSystem = nullptr;

	delete m_camera;
	m_camera = nullptr;
}

void GameplayGameState::ProcessInput()
{
	if(m_player->GetStateMachine()->IsInState(*PlayerHurtState::Instance()) || 
		m_player->GetStateMachine()->IsInState(*PlayerKnockbackState::Instance()) ||
		m_player->GetStateMachine()->IsInState(*PlayerDeadState::Instance()))
		return;

	auto gamePadState = m_input->GetGamePadState();
	auto buttons = m_input->GetGamePadButtons();

	if(m_input->IsKeyDown(ESC_KEY) || gamePadState.IsMenuPressed())
		PostQuitMessage(0);

#ifdef _DEBUG
	if(m_input->IsKeyDown('R') || gamePadState.IsViewPressed())
		ResetGame();

	if(m_input->WasKeyPressed(F4_KEY))
	{
		ToggleHitBoxes();
	}
#endif

	if(m_input->IsKeyDown(PLAYER_UP_KEY) || gamePadState.IsDPadUpPressed() || gamePadState.IsLeftThumbStickUp() &&
		!m_input->IsKeyDown(PLAYER_DOWN_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) || gamePadState.IsDPadLeftPressed() || gamePadState.IsLeftThumbStickLeft() &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			m_player->Move(UnitVectors::UpLeft);
		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) || gamePadState.IsDPadRightPressed() || gamePadState.IsLeftThumbStickRight() &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			m_player->Move(UnitVectors::UpRight);
		}
		else
		{
			m_player->Move(UnitVectors::Up);
		}
	}
	else if(m_input->IsKeyDown(PLAYER_DOWN_KEY) || gamePadState.IsDPadDownPressed() || gamePadState.IsLeftThumbStickDown())
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) || gamePadState.IsDPadLeftPressed() || gamePadState.IsLeftThumbStickLeft() &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			m_player->Move(UnitVectors::DownLeft);
		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) || gamePadState.IsDPadRightPressed() || gamePadState.IsLeftThumbStickRight() &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			m_player->Move(UnitVectors::DownRight);
		}
		else
		{
			m_player->Move(UnitVectors::Down);
		}
	}
	else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) || gamePadState.IsDPadRightPressed() || gamePadState.IsLeftThumbStickRight() &&
		!m_input->IsKeyDown(PLAYER_LEFT_KEY))
	{
		m_player->Move(UnitVectors::Right);
	}
	else if(m_input->IsKeyDown(PLAYER_LEFT_KEY) || gamePadState.IsDPadLeftPressed() || gamePadState.IsLeftThumbStickLeft() &&
		!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		m_player->Move(UnitVectors::Left);
	}

	if(m_input->WasKeyPressed(PLAYER_RIGHT_KEY) || 
		m_input->WasGamePadButtonPressed(buttons.dpadRight) || m_input->WasGamePadButtonPressed(buttons.leftStickRight))
	{
		m_controlSystem->SetControlsPressed(Controls::Right);
		m_controlSystem->ResetDoubleTap();
			
		if(m_controlSystem->GetLastKeyPressed() == Controls::Right &&
			m_controlSystem->CanRun())
		{
			m_player->Run();
		}
	}
	
	if(m_input->WasKeyPressed(PLAYER_LEFT_KEY) || 
		m_input->WasGamePadButtonPressed(buttons.dpadLeft) || m_input->WasGamePadButtonPressed(buttons.leftStickLeft))
	{
		m_controlSystem->SetControlsPressed(Controls::Left);
		m_controlSystem->ResetDoubleTap();

		if(m_controlSystem->GetLastKeyPressed() == Controls::Left &&
			m_controlSystem->CanRun())
		{
			m_player->Run();
		}
	}

	if(m_input->IsKeyDown(PLAYER_Z_KEY) || gamePadState.IsBPressed())
	{
		m_player->Block();
		return;
	}
	else if(m_player->GetStateMachine()->IsInState(*PlayerBlockState::Instance()))
	{
		m_player->GetStateMachine()->ChangeState(PlayerIdleState::Instance());
	}

	if(m_input->WasKeyPressed(PLAYER_X_KEY) || m_input->WasGamePadButtonPressed(buttons.x))
	{
		m_controlSystem->SetControlsPressed(Controls::NormalAttack);
		m_controlSystem->ResetComboTimer();
		return;
	}

	if(m_input->WasKeyPressed(PLAYER_C_KEY) || m_input->WasGamePadButtonPressed(buttons.y))
	{
		m_controlSystem->SetControlsPressed(Controls::StrongAttack);
		m_controlSystem->ResetComboTimer();
		return;
	}

	if(!(m_input->IsKeyDown(PLAYER_UP_KEY) || gamePadState.IsDPadUpPressed() || gamePadState.IsLeftThumbStickUp() ||
		m_input->IsKeyDown(PLAYER_DOWN_KEY) || gamePadState.IsDPadDownPressed() || gamePadState.IsLeftThumbStickDown() ||
		m_input->IsKeyDown(PLAYER_LEFT_KEY) || gamePadState.IsDPadLeftPressed() || gamePadState.IsLeftThumbStickLeft() ||
		m_input->IsKeyDown(PLAYER_RIGHT_KEY) || gamePadState.IsDPadRightPressed() || gamePadState.IsLeftThumbStickRight() ||
		m_input->IsKeyDown(PLAYER_X_KEY) ||
		m_input->IsKeyDown(PLAYER_Z_KEY) ||
		m_input->WasKeyPressed(PLAYER_C_KEY)))
	{
		m_player->Move(Vector2::Zero);
		m_player->Walk();
	}
}

void GameplayGameState::Update(float deltaTime)
{
	UIManager::Update(deltaTime);

	if(UIManager::IsFading()) return;

	m_deltaTime = deltaTime;
	m_sceneStateMachine->Update();
	Tick(deltaTime);
}

void GameplayGameState::CheckForEncounter()
{
	if(m_camera->GetPosition().x < m_encounterHandler->GetEncounterPosition())
		return;

	m_sceneStateMachine->ChangeState(EncounterSceneState::Instance());
}

void GameplayGameState::Tick(float deltaTime)
{
	if(m_stopTimer > 0)
	{
		m_stopTimer -= deltaTime;
		return;
	}

	if(m_collisionCooldown > 0)
		m_collisionCooldown -= deltaTime;

	if(m_collisionCooldown <= 0)
		m_isCollisionOnCooldown = false;

	m_controlSystem->Update(deltaTime);
	m_camera->Update(deltaTime);
	m_player->Update(deltaTime);
	m_NPCManager->Update(deltaTime);

	if(m_player->IsDead() && m_player->GetLives() > 0)
		m_player->Respawn();

	m_impactFx->Update(deltaTime);
	m_particleSystem->Update(deltaTime);
}

void GameplayGameState::ProcessCollisions()
{
	if(m_stopTimer > 0 || m_isCollisionOnCooldown)	return;

	std::vector<Enemy*> enemyList = m_NPCManager->GetEnemyList();

	auto isPlayerHitBoxActive = m_player->GetHitBoxManager()->IsHitBoxActive();
	auto playerGroundPositionX = m_player->GetGroundPosition().x;
	auto playerGroundPositionY = m_player->GetGroundPosition().y;
	auto playerPushBox = m_player->GetHitBoxManager()->GetPushBox();

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		Enemy* enemy = enemyList[i];

		auto enemyPushBox = enemy->GetHitBoxManager()->GetPushBox();

		if(playerPushBox.OnCollision(enemyPushBox))
		{
			float resolve = 0;

			float xDiff = (playerPushBox.GetLeft() + (playerPushBox.GetWidth() * 0.5f)) - (enemyPushBox.GetLeft() + (enemyPushBox.GetWidth() * 0.5f));
			float yDiff = (playerPushBox.GetTop() + (playerPushBox.GetHeight() * 0.5f)) - (enemyPushBox.GetTop() + (enemyPushBox.GetHeight() * 0.5f));

			if(fabs(xDiff) > fabs(yDiff))
			{
				if(xDiff > 0)
				{
					resolve = (enemyPushBox.GetLeft() + enemyPushBox.GetWidth()) - playerPushBox.GetLeft();
				}
				else
				{
					resolve = -((playerPushBox.GetLeft() + playerPushBox.GetWidth()) - enemyPushBox.GetLeft());
				}

				m_player->SetPosition(playerGroundPositionX + resolve, playerGroundPositionY);
			}
			else
			{
				if(yDiff > 0)
				{
					resolve = (enemyPushBox.GetTop() + enemyPushBox.GetHeight()) - playerPushBox.GetTop();
				}
				else // Colliding below
				{
					resolve = -((playerPushBox.GetTop() + playerPushBox.GetHeight()) - enemyPushBox.GetTop());
				}

				m_player->SetPosition(playerGroundPositionX, playerGroundPositionY + resolve);
			}
		}

		// true if player hitbox is active and enemy is in vertical range
		if(isPlayerHitBoxActive &&
			fabs(enemy->GetGroundPosition().y - playerGroundPositionY) < VerticalHitRange)
		{
			// check player has hit an enemy
			if(m_player->GetHitBoxManager()->GetHitBox().OnCollision(
				enemy->GetHitBoxManager()->GetHurtBox()))
			{
				auto damageData = m_player->GetDamageData();
				auto groundPosition = enemy->GetGroundPosition();
				auto frameData = enemy->GetSprite()->GetFrameData(enemy->GetAnimator()->GetCurrentFrame());
				auto spriteHeight = frameData.spriteSourceSize.bottom;
				auto normalDirection = Vector2(enemy->GetGroundPosition() - m_player->GetGroundPosition());
				normalDirection.Normalize();

				enemy->ApplyDamage(m_player, damageData.amount);
				enemy->ShowEnemyHud();

				m_player->IncreaseSpecial();
				m_player->GetControlSystem()->IncrementHitComboCount();

				if(enemy->GetHealth() <= 0.0f) m_player->AddKill();

				m_stopTimer = damageData.hitStopDuration;
				m_isCollisionOnCooldown = true;
				m_collisionCooldown = damageData.hitStopDuration;

				m_impactFx->DisplayFx(Vector2(groundPosition.x, groundPosition.y - spriteHeight * 0.5f));
				SpawnParticles(m_impactFx->Position(), normalDirection, (Color)Colors::Green, (Color)Colors::DarkGreen, 1.0f, 200);

				return;
			}
		}

		// true if enemy hitbox is active and player is in vertical range
		if(enemy->GetHitBoxManager()->IsHitBoxActive() &&
			fabs(playerGroundPositionY - enemy->GetGroundPosition().y) < VerticalHitRange)
		{
			// check enemy has hit the player
			if(enemy->GetHitBoxManager()->GetHitBox().OnCollision(
				m_player->GetHitBoxManager()->GetHurtBox()))
			{
				auto damageData = enemy->GetDamageData();
				auto enemyVelocity = enemy->GetCurrentVelocity();
				enemyVelocity.Normalize();
				auto normalDirection = m_player->GetGroundPosition() - enemy->GetGroundPosition();
				normalDirection.Normalize();

				auto frameData = m_player->GetSprite()->GetFrameData(m_player->GetAnimator()->GetCurrentFrame());
				auto spriteHeight = frameData.spriteSourceSize.bottom;

				m_player->ApplyDamage(enemy, damageData.amount);
				m_player->SetPositionX(m_player->GetPositionX() + enemyVelocity.x);
				m_player->IncreaseSpecial();
				
				if(m_player->GetFacingDirection() == enemy->GetFacingDirection())
					m_player->FlipHorizontally(m_player->GetFacingDirection() != Vector3::Left);

				enemy->ShowEnemyHud();

				m_stopTimer = damageData.hitStopDuration;
				m_isCollisionOnCooldown = true;
				m_collisionCooldown = damageData.hitStopDuration;
				
				m_impactFx->DisplayFx(Vector2(playerGroundPositionX, playerGroundPositionY - spriteHeight * 0.5f));

				if(m_player->GetStateMachine()->IsInState(*PlayerBlockState::Instance()))
				{
					m_player->SetPositionX((m_player->GetGroundPosition() + Vector2(normalDirection * 2.0f)).x);
				}
				else 
				{
					SpawnParticles(m_impactFx->Position(), normalDirection, (Color)Colors::Red, (Color)Colors::DarkRed, 1.0f, 200);
				}
				
				return;
			}
		}
	}

	Vector2 playerBoundaryMin = m_playerBoundary.GetMin();
	Vector2 playerBoundaryMax = m_playerBoundary.GetMax();

	if(playerGroundPositionX < playerBoundaryMin.x)
	{
		m_player->SetPosition(Vector2(playerBoundaryMin.x, m_player->GetPositionY()));
		m_player->SetCurrentVelocity(Vector2(0.0f, m_player->GetCurrentVelocity().y));
		m_player->SetTargetVelocity(Vector2(0.0f, m_player->GetTargetVelocity().y));
	}

	if(playerGroundPositionY < playerBoundaryMin.y)
	{
		m_player->SetPosition(Vector2(m_player->GetPositionX(), playerBoundaryMin.y));
		m_player->SetCurrentVelocity(Vector2(m_player->GetCurrentVelocity().x, 0.0f));
		m_player->SetTargetVelocity(Vector2(m_player->GetTargetVelocity().x, 0.0f));
	}

	if(playerGroundPositionX > playerBoundaryMax.x)
	{
		m_player->SetPosition(Vector2(playerBoundaryMax.x, m_player->GetPositionY()));
		m_player->SetCurrentVelocity(Vector2(0.0f, m_player->GetCurrentVelocity().y));
		m_player->SetTargetVelocity(Vector2(0.0f, m_player->GetTargetVelocity().y));
	}

	if(playerGroundPositionY > playerBoundaryMax.y)
	{
		m_player->SetPosition(Vector2(m_player->GetPositionX(), playerBoundaryMax.y));
		m_player->SetCurrentVelocity(Vector2(m_player->GetCurrentVelocity().x, 0.0f));
		m_player->SetTargetVelocity(Vector2(m_player->GetTargetVelocity().x, 0.0f));
	}

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		Enemy* enemy = enemyList[i];

		if(enemy->GetGroundPosition().y > playerBoundaryMax.y)
		{
			enemy->SetPosition(enemy->GetPositionX(), playerBoundaryMax.y);
			enemy->SetCurrentVelocity(Vector2(enemy->GetCurrentVelocity().x, 0.0f));
			enemy->SetTargetVelocity(Vector2(enemy->GetTargetVelocity().x, 0.0f));
		}

		if(enemy->GetGroundPosition().y < playerBoundaryMin.y)
		{
			enemy->SetPosition(enemy->GetPositionX(), playerBoundaryMin.y);
			enemy->SetCurrentVelocity(Vector2(enemy->GetCurrentVelocity().x, 0.0f));
			enemy->SetTargetVelocity(Vector2(enemy->GetTargetVelocity().x, 0.0f));
		}
	}
}

void GameplayGameState::SpawnParticles(const Vector2& position, const Vector2& velocity, Color startColour, Color endColour, float lifeTime, unsigned int number)
{
	m_particleData.Velocity = velocity;
	m_particleData.Position = position;
	m_particleData.ColorBegin = startColour;
	m_particleData.ColorEnd = endColour;
	m_particleData.LifeTime = lifeTime;

	for (unsigned int i = 0; i < number; i++)
	{
		m_particleData.VelocityVariation.x = (Randomiser::Instance()->GetRandNum(1.0f, 5.0f));
		m_particleData.VelocityVariation.y = (Randomiser::Instance()->GetRandNum(-10.0f, 1.0f));
		m_particleData.VelocityVariation.Normalize();
		m_particleData.VelocityVariation *= Randomiser::Instance()->GetRandNum(1.0f, 40.0f);

		m_particleSystem->Emit(m_particleData);
	}
}

void GameplayGameState::Render()
{
	m_levelRenderer->Render(m_graphics);
	m_player->Render(m_graphics);
	m_NPCManager->Render(m_graphics);
	m_particleSystem->Render(m_graphics); 
	m_impactFx->Render(m_graphics);
	UIManager::Render(m_graphics);
}

void GameplayGameState::ResetGame()
{
	m_input->ClearAll();
	m_player->Reset();
	m_NPCManager->Reset();
	m_camera->Reset();
	m_camera->SetTarget(m_player);
	m_sceneStateMachine->ChangeState(TravellingSceneState::Instance());
	m_encounterHandler->SetEncounterIndex(0);
	SetPlayerBoundaryX(StartingBoundaryMinX, (float)m_levelRenderer->GetLevelPixelWidth());
}

void GameplayGameState::SetPlayerBoundaryX(float minX, float maxX)
{
	Vector2 newMin = Vector2(minX, m_playerBoundary.GetMin().y);
	Vector2 newMax = Vector2(maxX, m_playerBoundary.GetMax().y);
	
	m_playerBoundary.SetAABB(AABB(newMin, newMax));
}

void GameplayGameState::ToggleHitBoxes()
{
	m_displayHitBoxes = !m_displayHitBoxes;

	m_player->GetHitBoxManager()->SetVisible(m_displayHitBoxes);

	auto npcList = m_NPCManager->GetEnemyList();

	for(Enemy* enemy : npcList)
	{
		enemy->GetHitBoxManager()->SetVisible(m_displayHitBoxes);
	}
}