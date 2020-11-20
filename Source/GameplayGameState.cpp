#include "GameplayGameState.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "Camera.h"
#include "ControlSystem.h"
#include "Texture.h"
#include "AnimatedSprite.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include "Animator.h"
#include "Player.h"
#include "Background.h"
#include "InGameHudManager.h"
#include "Resources.h"
#include "UnitVectors.h"
#include "HitBoxManager.h"
#include "NPCManager.h"
#include "Enemy.h"
#include "pch.h"
#include "Error.h"
#include "StateMachine.h"
#include "GameplayOwnedSceneStates.h"
#include "EncounterHandler.h"
#include "TravellingHandler.h"
#include "TravelPrompt.h"

using namespace GlobalConstants;
using namespace InGameHudConstants;

GameplayGameState::GameplayGameState() :
	m_gameStateManager(nullptr),
	m_graphics(nullptr),
	m_input(nullptr),
	m_camera(nullptr),
	m_controlSystem(nullptr),
	m_playerTexture(nullptr),
	m_enemyTexture(nullptr),
	m_mookPortraitTexture(nullptr),
	m_hitBoxTexture(nullptr),
	m_shadowTexture(nullptr),
	m_backgroundTexture(nullptr),
	m_playerSprite(nullptr),
	m_playerShadowSprite(nullptr),
	m_enemySprite(nullptr),
	m_mookPortraitSprite(nullptr),
	m_enemyShadowSprite(nullptr),
	m_hitBoxSprite(nullptr),
	m_backgroundSprite(nullptr),
	m_playerAnimator(nullptr),
	m_enemyAnimator(nullptr),
	m_playerHitBoxManager(nullptr),
	m_enemyHitBoxManager(nullptr),
	m_NPCManager(nullptr),
	m_player(nullptr),
	m_background(nullptr),
	m_hudManager(nullptr),
	m_sceneStateMachine(nullptr),
	m_encounterHandler(nullptr),
	m_travellingHandler(nullptr),
	m_canAttack(true),
	m_running(false),
	m_playerBoundary(AABB()),
	m_deltaTime(0.0f),
	GameState(L"GAMEPLAY")
{}

GameplayGameState::GameplayGameState(GameStateManager* gameStateManager) : GameplayGameState()
{
	m_gameStateManager = gameStateManager;
	m_graphics = m_gameStateManager->GetGraphics();
	m_input = m_gameStateManager->GetInput();
}

GameplayGameState::~GameplayGameState()
{
}

void GameplayGameState::OnEntry()
{
	LoadAssets();
}

void GameplayGameState::OnExit()
{
	ReleaseAll();
	DeleteAssets();
}

void GameplayGameState::LoadAssets()
{
	m_camera = new Camera();
	m_controlSystem = new ControlSystem();

	m_playerTexture = new Texture();
	m_enemyTexture = new Texture();
	m_mookPortraitTexture = new Texture();
	m_hitBoxTexture = new Texture();
	m_shadowTexture = new Texture();
	m_backgroundTexture = new Texture();

	m_playerSprite = new Spritesheet();
	m_playerShadowSprite = new Sprite();
	m_enemySprite = new Spritesheet();
	m_mookPortraitSprite = new Sprite();
	m_enemyShadowSprite = new Sprite();
	m_hitBoxSprite = new Sprite();
	m_backgroundSprite = new Sprite();

	m_playerAnimator = new Animator();
	m_enemyAnimator = new Animator();

	m_playerHitBoxManager = new HitBoxManager();
	m_enemyHitBoxManager = new HitBoxManager();

	m_NPCManager = new NPCManager();

	m_player = new Player();
	m_background = new Background();
	m_hudManager = new InGameHudManager();
	m_sceneStateMachine = new StateMachine<GameplayGameState>(this);
	m_encounterHandler = new EncounterHandler();
	m_travellingHandler = new TravellingHandler();

	m_playerTexture->LoadTexture(m_graphics, "GameData\\Sprites\\playerSpriteSheet.png");
	m_enemyTexture->LoadTexture(m_graphics, "GameData\\Sprites\\enemySpritesheet.png");
	m_mookPortraitTexture->LoadTexture(m_graphics, "GameData\\Sprites\\UI\\mook_hud_portrait.png");
	m_hitBoxTexture->LoadTexture(m_graphics, "GameData\\Sprites\\hitbox.png");
	m_shadowTexture->LoadTexture(m_graphics, "GameData\\Sprites\\shadow.png");
	m_backgroundTexture->LoadTexture(m_graphics, "GameData\\Sprites\\backgroundTest.png");

	m_playerSprite->Init(m_playerTexture, "GameData\\SpriteSheetData\\playerSpritesheetData.json");
	m_playerShadowSprite->Init(m_shadowTexture);
	m_playerShadowSprite->SetAlpha(0.7f);
	m_enemySprite->Init(m_enemyTexture, "GameData\\SpriteSheetData\\enemySpritesheetData.json");
	m_mookPortraitSprite->Init(m_mookPortraitTexture);
	m_mookPortraitSprite->SetOrigin(Vector2::Zero);
	m_mookPortraitSprite->SetPosition(Vector2(EnemyPortraitPositionX, EnemyPortraitPositionY));
	m_enemyShadowSprite->Init(m_shadowTexture);
	m_enemyShadowSprite->SetAlpha(0.7f);
	m_hitBoxSprite->Init(m_hitBoxTexture);
	m_backgroundSprite->Init(m_backgroundTexture);
	m_backgroundSprite->SetOrigin(Vector2::Zero);

	m_playerAnimator->Init("GameData\\AnimationData\\playerAnimationData.json");
	m_enemyAnimator->Init("GameData\\AnimationData\\enemyAnimationData.json");

	m_playerHitBoxManager->Init(m_hitBoxSprite, m_player, "GameData\\HitBoxData\\playerHitBoxData.json");
	m_enemyHitBoxManager->Init(m_hitBoxSprite, "GameData\\HitBoxData\\enemyHitBoxData.json");

	m_player->LoadData("GameData\\PlayerData\\playerData.txt", "GameData\\PlayerData\\playerDamage.txt");
	m_player->Init(m_playerSprite, m_playerShadowSprite, m_playerAnimator, m_playerHitBoxManager, m_controlSystem);
	m_player->SetCamera(m_camera);
	m_camera->SetTarget(m_player);

	m_NPCManager->Init();

	std::vector<Enemy*> enemyList = m_NPCManager->GetEnemyList();

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->SetPlayerTarget(m_player);

		enemyList[i]->Init(m_graphics, enemyList[i]->GetData().objectData.startingPosition, m_enemySprite, m_enemyShadowSprite, m_enemyAnimator, m_enemyHitBoxManager, m_hudManager, m_mookPortraitSprite);

		std::string type = enemyList[i]->GetData().type;
		std::string enemyDataFile = "GameData\\EnemyData\\Damage\\" + type + "Damage.txt";
		
		if(!enemyList[i]->LoadDamageData(enemyDataFile))
		{
			std::string error = "Error! Enemy damage data " + enemyDataFile + " not found.";
			Error::FileLog(error);
		}
		
		enemyList[i]->GetHitBoxManager()->SetOwner(enemyList[i]);
		enemyList[i]->SetCamera(m_camera);
		enemyList[i]->SetActive(false);
	}

	m_background->Init(m_backgroundSprite);
	m_background->SetCamera(m_camera);
	m_hudManager->Init(m_graphics);

	m_hudManager->SetMaxPlayerHealth(m_player->GetMaxHealth());
	m_hudManager->SetCurrentPlayerHealth(m_player->GetHealth());
	
	m_sceneStateMachine->Init(TravellingSceneState::Instance(), nullptr, GlobalSceneState::Instance());
	m_encounterHandler->Init("GameData\\EncounterData\\encounterPositions.txt", m_NPCManager->GetEnemyList());

	m_playerBoundary.SetMin(Vector2(StartingBoundaryMinX, StartingBoundaryMinY));
	m_playerBoundary.SetMax(Vector2((float)m_background->GetSprite()->GetWidth() - 1.0f, (float)m_graphics->GetHeight() - 1.0f));
	
	m_camera->Init(GameWidth);
	
	m_running = true;
}

void GameplayGameState::DeleteAssets()
{
	if(m_travellingHandler != nullptr)
	{
		delete m_travellingHandler;
		m_travellingHandler = nullptr;
	}

	if(m_encounterHandler != nullptr)
	{
		delete m_encounterHandler;
		m_encounterHandler = nullptr;
	}

	if(m_sceneStateMachine != nullptr)
	{
		delete m_sceneStateMachine;
		m_sceneStateMachine = nullptr;
	}

	if(m_hudManager != nullptr)
	{
		delete m_hudManager;
		m_hudManager = nullptr;
	}

	if(m_background)
	{
		delete m_background;
		m_background = nullptr;
	}

	if(m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	if(m_NPCManager)
	{
		delete m_NPCManager;
		m_NPCManager = nullptr;
	}

	if(m_enemyHitBoxManager)
	{
		delete m_enemyHitBoxManager;
		m_enemyHitBoxManager = nullptr;
	}

	if(m_enemyAnimator)
	{
		delete m_enemyAnimator;
		m_enemyAnimator = nullptr;
	}

	if(m_playerAnimator)
	{
		delete m_playerAnimator;
		m_playerAnimator = nullptr;
	}

	if(m_backgroundSprite)
	{
		delete m_backgroundSprite;
		m_backgroundSprite = nullptr;
	}

	if(m_hitBoxSprite)
	{
		delete m_hitBoxSprite;
		m_hitBoxSprite = nullptr;
	}

	if(m_enemyShadowSprite)
	{
		delete m_enemyShadowSprite;
		m_enemyShadowSprite = nullptr;
	}

	if(m_mookPortraitSprite)
	{
		delete m_mookPortraitSprite;
		m_mookPortraitSprite = nullptr;
	}

	if(m_enemySprite)
	{
		delete m_enemySprite;
		m_enemySprite = nullptr;
	}

	if(m_playerShadowSprite)
	{
		delete m_playerShadowSprite;
		m_playerShadowSprite = nullptr;
	}

	if(m_playerSprite)
	{
		delete m_playerSprite;
		m_playerSprite = nullptr;
	}

	if(m_backgroundTexture)
	{
		delete m_backgroundTexture;
		m_backgroundTexture = nullptr;
	}

	if(m_shadowTexture)
	{
		delete m_shadowTexture;
		m_shadowTexture = nullptr;
	}

	if(m_hitBoxTexture)
	{
		delete m_hitBoxTexture;
		m_hitBoxTexture = nullptr;
	}

	if(m_mookPortraitTexture)
	{
		delete m_mookPortraitTexture;
		m_mookPortraitTexture = nullptr;
	}

	if(m_enemyTexture)
	{
		delete m_enemyTexture;
		m_enemyTexture = nullptr;
	}

	if(m_playerTexture)
	{
		delete m_playerTexture;
		m_playerTexture = nullptr;
	}

	if(m_controlSystem)
	{
		delete m_controlSystem;
		m_controlSystem = nullptr;
	}

	if(m_camera)
	{
		delete m_camera;
		m_camera = nullptr;
	}
}

void GameplayGameState::ProcessInput()
{
	if(m_input->IsKeyDown(ESC_KEY))
	{
		PostQuitMessage(0);
	}

	if(m_input->IsKeyDown('R'))
	{
		ResetGame();
	}

	if(m_input->IsKeyDown(PLAYER_UP_KEY) &&
		!m_input->IsKeyDown(PLAYER_DOWN_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			m_controlSystem->SetInput(UpLeft);
		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			m_controlSystem->SetInput(UpRight);
		}
		else
		{
			m_controlSystem->SetInput(Up);
		}
	}
	else if(m_input->IsKeyDown(PLAYER_DOWN_KEY) &&
		!m_input->IsKeyDown(PLAYER_UP_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			m_controlSystem->SetInput(DownLeft);

		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			m_controlSystem->SetInput(DownRight);
		}
		else
		{
			m_controlSystem->SetInput(Down);
		}
	}
	else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
		!m_input->IsKeyDown(PLAYER_LEFT_KEY))
	{
		m_controlSystem->SetInput(Right);
	}
	else if(m_input->IsKeyDown(PLAYER_LEFT_KEY) && 
		!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		m_controlSystem->SetInput(Left);
	}

	if(m_input->IsKeyDown(PLAYER_A_KEY) &&
		m_controlSystem->CanAttack())
	{
		m_controlSystem->SetInput(Attack);
		m_controlSystem->CanAttack(false);
		return;
	}

	if(!(m_input->IsKeyDown(PLAYER_UP_KEY) ||
		m_input->IsKeyDown(PLAYER_DOWN_KEY) ||
		m_input->IsKeyDown(PLAYER_LEFT_KEY) ||
		m_input->IsKeyDown(PLAYER_RIGHT_KEY) ||
		m_input->IsKeyDown(PLAYER_A_KEY)))
	{
		m_controlSystem->SetInput(None);
	}

	if(!m_input->IsKeyDown(PLAYER_A_KEY))
	{
		m_controlSystem->CanAttack(true);
	}
}

void GameplayGameState::Update(float deltaTime)
{
	m_deltaTime = deltaTime;
	m_sceneStateMachine->Update();
}

void GameplayGameState::CheckForEncounter()
{
	if(m_camera->GetPosition().x < m_encounterHandler->GetEncounterPosition())
		return;

	m_sceneStateMachine->ChangeState(EncounterSceneState::Instance());
}

void GameplayGameState::Tick(float deltaTime)
{
	m_player->Update(deltaTime);
	m_camera->Update(deltaTime);
	m_NPCManager->Update(deltaTime);
	m_background->Update(deltaTime);
	m_hudManager->SetMaxPlayerHealth(m_player->GetMaxHealth());
	m_hudManager->SetCurrentPlayerHealth(m_player->GetHealth());
	m_hudManager->UpdatePlayerLives(m_player->GetLives());
	m_hudManager->GetTravelPrompt()->Update(deltaTime);

	if(m_player->IsDead() && m_player->GetLives() > 0)
		m_player->Respawn();
}

void GameplayGameState::ProcessCollisions()
{
	std::vector<Enemy*> enemyList = m_NPCManager->GetEnemyList();

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		Enemy* enemy = enemyList[i];

		// true if player hitbox is active and 
		if(m_player->GetHitBoxManager()->IsHitBoxActive() &&
			enemy->GetGroundPosition().y - m_player->GetGroundPosition().y < 8.0f)
		{
			// check player hitbox vs enemy hurtboxes
			if(m_player->GetHitBoxManager()->GetHitBox().OnCollision(
				enemy->GetHitBoxManager()->GetHurtBox()))
			{
				enemy->ApplyDamage(m_player, m_player->GetDamage());
				enemy->ShowEnemyHud();
			}
		}

		if(enemy->GetHitBoxManager()->IsHitBoxActive() &&
			m_player->GetGroundPosition().y - enemy->GetGroundPosition().y < 8.0f)
		{
			// check player hitbox vs enemy hurtboxes
			if(enemy->GetHitBoxManager()->GetHitBox().OnCollision(
				m_player->GetHitBoxManager()->GetHurtBox()))
			{
				m_player->ApplyDamage(enemy, enemy->GetDamage());
				enemy->ShowEnemyHud();
			}
		}
	}

	Vector2 playerBoundaryMin = m_playerBoundary.GetMin();
	Vector2 playerBoundaryMax = m_playerBoundary.GetMax();

	if(m_player->GetGroundPosition().x < playerBoundaryMin.x)
	{
		m_player->SetPosition(Vector2(playerBoundaryMin.x, m_player->GetPositionY()));
		m_player->SetCurrentVelocity(Vector2(0.0f, m_player->GetCurrentVelocity().y));
		m_player->SetTargetVelocity(Vector2(0.0f, m_player->GetTargetVelocity().y));
	}

	if(m_player->GetGroundPosition().y < playerBoundaryMin.y)
	{
		m_player->SetPosition(Vector2(m_player->GetPositionX(), playerBoundaryMin.y));
		m_player->SetCurrentVelocity(Vector2(m_player->GetCurrentVelocity().x, 0.0f));
		m_player->SetTargetVelocity(Vector2(m_player->GetTargetVelocity().x, 0.0f));
	}

	if(m_player->GetGroundPosition().x > playerBoundaryMax.x)
	{
		m_player->SetPosition(Vector2(playerBoundaryMax.x, m_player->GetPositionY()));
		m_player->SetCurrentVelocity(Vector2(0.0f, m_player->GetCurrentVelocity().y));
		m_player->SetTargetVelocity(Vector2(0.0f, m_player->GetTargetVelocity().y));
	}

	if(m_player->GetGroundPosition().y > playerBoundaryMax.y)
	{
		m_player->SetPosition(Vector2(m_player->GetPositionX(), playerBoundaryMax.y));
		m_player->SetCurrentVelocity(Vector2(m_player->GetCurrentVelocity().x, 0.0f));
		m_player->SetTargetVelocity(Vector2(m_player->GetTargetVelocity().x, 0.0f));
	}

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		Enemy* enemy = enemyList[i];

		if(enemy->GetGroundPosition().x < StartingBoundaryMinX)
		{
			enemy->SetPosition(Vector2(StartingBoundaryMinX, enemy->GetPositionY()));
			enemy->SetCurrentVelocity(Vector2(0.0f, enemy->GetCurrentVelocity().y));
			enemy->SetTargetVelocity(Vector2(0.0f, enemy->GetTargetVelocity().y));
		}

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

void GameplayGameState::Render()
{
	m_background->Render(m_graphics);
	m_player->Render(m_graphics);
	m_NPCManager->Render(m_graphics);
	m_hudManager->Render(m_graphics);
}

void GameplayGameState::ReleaseAll()
{
	if(m_hudManager) { m_hudManager->ReleaseAll(); }
	if(m_backgroundTexture) { m_backgroundTexture->Release(); }
	if(m_shadowTexture) { m_shadowTexture->Release(); }
	if(m_hitBoxTexture) { m_hitBoxTexture->Release(); }
	if(m_mookPortraitTexture) { m_mookPortraitTexture->Release(); }
	if(m_enemyTexture) { m_enemyTexture->Release(); }
	if(m_playerTexture) { m_playerTexture->Release(); }
}

void GameplayGameState::ResetGame()
{
	m_input->ClearAll();
	m_player->Reset();
	m_NPCManager->Reset();
	m_backgroundSprite->SetPosition(Vector2::Zero);
	m_camera->Reset();
	m_camera->SetTarget(m_player);
	m_hudManager->Reset();
	m_encounterHandler->SetEncounterIndex(0);
	m_sceneStateMachine->ChangeState(TravellingSceneState::Instance());
	SetPlayerBoundaryX(StartingBoundaryMinX, (float)m_background->GetSprite()->GetWidth());
}

void GameplayGameState::SetPlayerBoundaryX(float minX, float maxX)
{
	Vector2 newMin = Vector2(minX, m_playerBoundary.GetMin().y);
	Vector2 newMax = Vector2(maxX, m_playerBoundary.GetMax().y);
	
	m_playerBoundary.SetAABB(AABB(newMin, newMax));
}