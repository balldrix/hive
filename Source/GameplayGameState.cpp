#include "GameplayGameState.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "Texture.h"
#include "AnimatedSprite.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include "Animator.h"
#include "Player.h"
#include "Resources.h"
#include "UnitVectors.h"
#include "ControlSystem.h"
#include "HitBox.h"

GameplayGameState::GameplayGameState()
{}

GameplayGameState::GameplayGameState(GameStateManager* gameStateManager) :
	m_gameStateManager(nullptr),
	m_graphics(nullptr),
	m_input(nullptr),
	m_controlSystem(nullptr),
	m_playerTexture(nullptr),
	m_hitBoxTexture(nullptr),
	m_playerSprite(nullptr),
	m_hitBoxSprite(nullptr),
	m_playerAnimator(nullptr),
	m_player(nullptr),
	m_hitBox(nullptr),
	m_running(false),
	GameState(L"GAMEPLAY")
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
	// seed random generator
	srand((int)time(NULL));

	// init control system
	m_controlSystem = new ControlSystem();
	m_controlSystem->Init();

	// create texture memory
	m_playerTexture = new Texture();
	m_hitBoxTexture = new Texture();

	// create sprite memory 
	m_playerSprite = new SpriteSheet();
	m_hitBoxSprite = new Sprite();

	// create animator memory
	m_playerAnimator = new Animator();

	// create objects in memory
	m_player = new Player();
	m_hitBox = new HitBox();

	// load textures
	m_playerTexture->LoadTexture(m_graphics, "GameData\\Sprites\\playerSpritesheet.png");
	m_hitBoxTexture->LoadTexture(m_graphics, "GameData\\Sprites\\hitbox.png");

	// init sprites
	m_playerSprite->Init(m_playerTexture, "GameData\\SpriteSheetData\\playerSpritesheetData.json");
	m_hitBoxSprite->Init(m_hitBoxTexture);

	// init animator
	m_playerAnimator->Init("GameData\\AnimationData\\playerAnimationData.json");

	// init game objects
	m_player->Init(m_controlSystem, m_playerSprite, m_playerAnimator, Vector2((float)StartScreenPositionX, (float)StartScreenPositionY), m_hitBox);
	m_hitBox->Init(m_hitBoxSprite, Colors::Blue.v);

	// set running to true
	m_running = true;
}

void GameplayGameState::DeleteAssets()
{
	// delete control system
	if(m_controlSystem)
	{
		delete m_controlSystem;
		m_controlSystem = nullptr;
	}
	// delete game objects
	if(m_player)
	{
		delete m_player;
		m_player = nullptr;
	}

	// delete animators
	if(m_playerAnimator)
	{
		delete m_playerAnimator;
		m_playerAnimator = nullptr;
	}

	// delete sprites
	if(m_playerSprite)
	{
		delete m_playerSprite;
		m_playerSprite = nullptr;
	}

	// delete textures
	if(m_playerTexture)
	{
		delete m_playerTexture;
		m_playerTexture = nullptr;
	}
}

void GameplayGameState::ProcessInput()
{
	// quit when escape key is pressed
	if(m_input->IsKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	///////////////////////////////////////////
	// check if key is pressed down
	///////////////////////////////////////////

	if(m_input->IsKeyDown(PLAYER_UP_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			// send up left input to control system
			m_controlSystem->SetInput(UpLeft);
		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY))
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
	else if(m_input->IsKeyDown(PLAYER_DOWN_KEY))
	{
		if(m_input->IsKeyDown(PLAYER_LEFT_KEY))
		{
			// send down left input to control system
			m_controlSystem->SetInput(DownLeft);

		}
		else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY))
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
	else if(m_input->IsKeyDown(PLAYER_LEFT_KEY))
	{
		// send left input to control system
		m_controlSystem->SetInput(Left);

	}
	else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		// send right input to control system
		m_controlSystem->SetInput(Right);
	}
	else if(!(m_input->IsKeyDown(PLAYER_UP_KEY) ||
		m_input->IsKeyDown(PLAYER_DOWN_KEY) ||
		m_input->IsKeyDown(PLAYER_LEFT_KEY) ||
		m_input->IsKeyDown(PLAYER_RIGHT_KEY)))
	{
		// set player input to none
		m_controlSystem->SetInput(None);
	}
}

void GameplayGameState::Update(float deltaTime)
{
	// update control system
	m_controlSystem->Update(deltaTime);

	// update player
	m_player->Update(deltaTime);
}

void GameplayGameState::Render()
{
	//////////////////////////////////////
	// render background first

	//////////////////////////////////////
	// render game objects
	m_player->Render(m_graphics);
}

void GameplayGameState::ReleaseAll()
{
	// release all texture resources
	if(m_playerTexture) { m_playerTexture->Release(); }
}

void GameplayGameState::ResetGame()
{
}
