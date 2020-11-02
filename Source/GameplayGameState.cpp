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
#include "InGameUiManager.h"
#include "Resources.h"
#include "UnitVectors.h"
#include "HitBoxManager.h"
#include "NPCManager.h"
#include "Enemy.h"
#include "pch.h"
#include "Error.h"

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
	m_uiManager(nullptr),
	m_canAttack(true),
	m_running(false),
	m_worldWidth(0),
	m_worldHeight(0),
	GameState(L"GAMEPLAY")
{}

GameplayGameState::GameplayGameState(GameStateManager* gameStateManager) : GameplayGameState()
{
	// get essential pointers from gamestate manager
	m_gameStateManager = gameStateManager;
	m_graphics = m_gameStateManager->GetGraphics();
	m_input = m_gameStateManager->GetInput();
}

GameplayGameState::~GameplayGameState()
{
}

void GameplayGameState::OnEntry()
{
	// load assets for the gameplay state
	LoadAssets();
}

void GameplayGameState::OnExit()
{
	// release memory and delete assets
	ReleaseAll();
	DeleteAssets();
}

void GameplayGameState::LoadAssets()
{
	m_worldWidth = 1200;
	m_worldHeight = 80;

	// init camera
	m_camera = new Camera();
	m_camera->Init(GlobalConstants::GAME_WIDTH, GlobalConstants::GAME_HEIGHT, m_worldWidth);

	// init control system
	m_controlSystem = new ControlSystem();

	// create texture memory
	m_playerTexture = new Texture();
	m_enemyTexture = new Texture();
	m_mookPortraitTexture = new Texture();
	m_hitBoxTexture = new Texture();
	m_shadowTexture = new Texture();
	m_backgroundTexture = new Texture();

	// create sprite memory 
	m_playerSprite = new SpriteSheet();
	m_playerShadowSprite = new Sprite();

	m_enemySprite = new SpriteSheet();
	m_mookPortraitSprite = new Sprite();
	m_enemyShadowSprite = new Sprite();

	m_hitBoxSprite = new Sprite();
	m_backgroundSprite = new Sprite();

	// create animator memory
	m_playerAnimator = new Animator();
	m_enemyAnimator = new Animator();

	// create hitbox managers
	m_playerHitBoxManager = new HitBoxManager();
	m_enemyHitBoxManager = new HitBoxManager();

	// create enemy manager
	m_NPCManager = new NPCManager();

	// create objects in memory
	m_player = new Player();
	m_background = new Background();
	m_uiManager = new InGameUiManager();

	// load textures
	m_playerTexture->LoadTexture(m_graphics, "GameData\\Sprites\\playerSpriteSheet.png");
	m_enemyTexture->LoadTexture(m_graphics, "GameData\\Sprites\\enemySpritesheet.png");
	m_mookPortraitTexture->LoadTexture(m_graphics, "GameData\\Sprites\\UI\\mook_hud_portrait.png");
	m_hitBoxTexture->LoadTexture(m_graphics, "GameData\\Sprites\\hitbox.png");
	m_shadowTexture->LoadTexture(m_graphics, "GameData\\Sprites\\shadow.png");
	m_backgroundTexture->LoadTexture(m_graphics, "GameData\\Sprites\\backgroundTest.png");

	// init sprites
	m_playerSprite->Init(m_playerTexture, "GameData\\SpriteSheetData\\playerSpritesheetData.json");
	m_playerShadowSprite->Init(m_shadowTexture);
	m_playerShadowSprite->SetAlpha(0.7f);
	m_enemySprite->Init(m_enemyTexture, "GameData\\SpriteSheetData\\enemySpritesheetData.json");
	m_mookPortraitSprite->Init(m_mookPortraitTexture);
	m_mookPortraitSprite->SetOrigin(Vector2::Zero);
	m_mookPortraitSprite->SetPosition(Vector2(InGameHudConstants::EnemyPortraitPositionX,
		InGameHudConstants::EnemyPortraitPositionY));
	m_enemyShadowSprite->Init(m_shadowTexture);
	m_enemyShadowSprite->SetAlpha(0.7f);
	m_hitBoxSprite->Init(m_hitBoxTexture);
	m_backgroundSprite->Init(m_backgroundTexture);
	m_backgroundSprite->SetOrigin(Vector2::Zero);

	// init animator
	m_playerAnimator->Init("GameData\\AnimationData\\playerAnimationData.json");
	m_enemyAnimator->Init("GameData\\AnimationData\\enemyAnimationData.json");

	// init hitbox managers
	m_playerHitBoxManager->Init(m_hitBoxSprite, m_player, "GameData\\HitBoxData\\playerHitBoxData.json");
	m_enemyHitBoxManager->Init(m_hitBoxSprite, "GameData\\HitBoxData\\enemyHitBoxData.json");

	// init game objects
	m_player->LoadData("GameData\\PlayerData\\playerData.txt", "GameData\\PlayerData\\playerDamage.txt");
	m_player->Init(m_playerSprite, m_playerShadowSprite, m_playerAnimator, m_playerHitBoxManager, m_controlSystem);
	m_player->SetCamera(m_camera);
	m_camera->SetTarget(m_player);

	m_NPCManager->Init();

	std::vector<Enemy*> enemyList = m_NPCManager->GetEnemyList();

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->Init(enemyList[i]->GetData().objectData.startingPosition, m_enemySprite, m_enemyShadowSprite, m_enemyAnimator, m_enemyHitBoxManager, m_uiManager, m_mookPortraitSprite);

		std::string type = enemyList[i]->GetData().type;
		std::string enemyDataFile = "GameData\\EnemyData\\" + type + "\\" + type + "Damage.txt";
		
		if(!enemyList[i]->LoadDamageData(enemyDataFile))
		{
			std::string error = "Error! Enemy damage data " + enemyDataFile + " not found.";
			Error::FileLog(error);
		}
		
		enemyList[i]->SetPlayerTarget(m_player);
		enemyList[i]->GetHitBoxManager()->SetOwner(enemyList[i]);
		enemyList[i]->SetCamera(m_camera);
	}

	m_background->Init(m_backgroundSprite);
	m_background->SetCamera(m_camera);
	m_uiManager->Init(m_graphics);

	m_uiManager->SetMaxPlayerHealth(m_player->GetMaxHealth());
	m_uiManager->SetCurrentPlayerHealth(m_player->GetHealth());
	
	// set running to true
	m_running = true;
}

void GameplayGameState::DeleteAssets()
{
	if(m_uiManager)
	{
		delete m_uiManager;
		m_uiManager = nullptr;
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

	// delete hit box managers
	if(m_enemyHitBoxManager)
	{
		delete m_enemyHitBoxManager;
		m_enemyHitBoxManager = nullptr;
	}

	// delete animators
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

	// delete sprites
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

	// delete textures
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

	// delete control system
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
	// quit when escape key is pressed
	if(m_input->IsKeyDown(ESC_KEY))
	{
		PostQuitMessage(0);
	}

	if(m_input->IsKeyDown('R'))
	{
		ResetGame();
	}

	///////////////////////////////////////////
	// check if key is pressed down
	///////////////////////////////////////////

	if(m_input->IsKeyDown(PLAYER_UP_KEY) &&
		!m_input->IsKeyDown(PLAYER_DOWN_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			// send up left input to control system
			m_controlSystem->SetInput(UpLeft);
		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			// send up right input to control system
			m_controlSystem->SetInput(UpRight);
		}
		else
		{
			// send up input to control system
			m_controlSystem->SetInput(Up);
		}
	}
	else if(m_input->IsKeyDown(PLAYER_DOWN_KEY) &&
		!m_input->IsKeyDown(PLAYER_UP_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY) &&
			!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
		{
			// send down left input to control system
			m_controlSystem->SetInput(DownLeft);

		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
			!m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			// send down right input to control system
			m_controlSystem->SetInput(DownRight);
		}
		else
		{
			// send up input to control system
			m_controlSystem->SetInput(Down);

		}
	}
	else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY) &&
		!m_input->IsKeyDown(PLAYER_LEFT_KEY))
	{
		// send right input to control system
		m_controlSystem->SetInput(Right);

	}
	else if(m_input->IsKeyDown(PLAYER_LEFT_KEY) && 
		!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		// send left input to control system
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
		// set player input to none
		m_controlSystem->SetInput(None);
	}

	if(!m_input->IsKeyDown(PLAYER_A_KEY))
	{
		m_controlSystem->CanAttack(true);
	}
}

void GameplayGameState::Update(float deltaTime)
{
	m_player->Update(deltaTime);
	m_camera->Update(deltaTime);
	m_NPCManager->Update(deltaTime);
	m_background->Update(deltaTime);
	m_uiManager->SetMaxPlayerHealth(m_player->GetMaxHealth());
	m_uiManager->SetCurrentPlayerHealth(m_player->GetHealth());

	if(m_player->IsDead())
	{
		ResetGame();
	}
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
			}
		}
	}

	// check player position against world objects
	if(m_player->GetGroundPosition().x < 1.0f)
	{
		m_player->SetPosition(Vector2(1.0f, m_player->GetPositionY()));
		m_player->SetCurrentVelocity(Vector2(0.0f, m_player->GetCurrentVelocity().y));
		m_player->SetTargetVelocity(Vector2(0.0f, m_player->GetTargetVelocity().y));
	}

	if(m_player->GetGroundPosition().y < 61.0f)
	{
		m_player->SetPosition(Vector2(m_player->GetPositionX(), 61.0f));
		m_player->SetCurrentVelocity(Vector2(m_player->GetCurrentVelocity().x, 0.0f));
		m_player->SetTargetVelocity(Vector2(m_player->GetTargetVelocity().x, 0.0f));
	}

	if(m_player->GetGroundPosition().x > m_worldWidth - 1)
	{
		m_player->SetPosition(Vector2((float)m_worldWidth - 1, m_player->GetPositionY()));
		m_player->SetCurrentVelocity(Vector2(0.0f, m_player->GetCurrentVelocity().y));
		m_player->SetTargetVelocity(Vector2(0.0f, m_player->GetTargetVelocity().y));
	}

	if(m_player->GetGroundPosition().y > m_graphics->GetHeight() - 1)
	{
		m_player->SetPosition(Vector2(m_player->GetPositionX(), m_graphics->GetHeight() - 1));
		m_player->SetCurrentVelocity(Vector2(m_player->GetCurrentVelocity().x, 0.0f));
		m_player->SetTargetVelocity(Vector2(m_player->GetTargetVelocity().x, 0.0f));
	}

	for(size_t i = 0; i < enemyList.size(); i++)
	{
		Enemy* enemy = enemyList[i];

		// check enemy position against world objects
		if(enemy->GetGroundPosition().x < 1.0f)
		{
			enemy->SetPosition(Vector2(1.0f, enemy->GetPositionY()));
			enemy->SetCurrentVelocity(Vector2(0.0f, enemy->GetCurrentVelocity().y));
			enemy->SetTargetVelocity(Vector2(0.0f, enemy->GetTargetVelocity().y));
		}

		if(enemy->GetGroundPosition().y < 61.0f)
		{
			enemy->SetPosition(Vector2(enemy->GetPositionX(), 61.0f));
			enemy->SetCurrentVelocity(Vector2(enemy->GetCurrentVelocity().x, 0.0f));
			enemy->SetTargetVelocity(Vector2(enemy->GetTargetVelocity().x, 0.0f));
		}

		if(enemy->GetGroundPosition().x > m_worldWidth - 1)
		{
			enemy->SetPosition(Vector2((float)m_worldWidth - 1, enemy->GetPositionY()));
			enemy->SetCurrentVelocity(Vector2(0.0f, enemy->GetCurrentVelocity().y));
			enemy->SetTargetVelocity(Vector2(0.0f, enemy->GetTargetVelocity().y));
		}

		if(enemy->GetGroundPosition().y > m_graphics->GetHeight() - 1)
		{
			enemy->SetPosition(Vector2(enemy->GetPositionX(), m_graphics->GetHeight() - 1));
			enemy->SetCurrentVelocity(Vector2(enemy->GetCurrentVelocity().x, 0.0f));
			enemy->SetTargetVelocity(Vector2(enemy->GetTargetVelocity().x, 0.0f));
		}
	}
}

void GameplayGameState::Render()
{
	//////////////////////////////////////
	// render background first

	// TODO refactor background it's own class
	m_background->Render(m_graphics);

	//////////////////////////////////////
	// render game objects
	m_player->Render(m_graphics);
	m_NPCManager->Render(m_graphics);
	m_uiManager->Render(m_graphics);
}

void GameplayGameState::ReleaseAll()
{
	// release all texture resources
	if(m_uiManager) { m_uiManager->ReleaseAll(); }
	if(m_backgroundTexture) { m_backgroundTexture->Release(); }
	if(m_shadowTexture) { m_shadowTexture->Release(); }
	if(m_hitBoxTexture) { m_hitBoxTexture->Release(); }
	if(m_mookPortraitTexture) { m_mookPortraitTexture->Release(); }
	if(m_enemyTexture) { m_enemyTexture->Release(); }
	if(m_playerTexture) { m_playerTexture->Release(); }
}

void GameplayGameState::ResetGame()
{
	m_player->Reset();
	m_NPCManager->Reset();
	m_backgroundSprite->SetPosition(Vector2::Zero);
	m_camera->Reset();
	m_uiManager->SetKillCount(0);
}
