#include "GameplayGameState.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "Texture.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "Player.h"
#include "Controls.h"
#include "Resources.h"
#include "UnitVectors.h"

GameplayGameState::GameplayGameState()
{}

GameplayGameState::GameplayGameState(GameStateManager* gameStateManager) :
	m_gameStateManager(nullptr),
	m_graphics(nullptr),
	m_input(nullptr),
	m_playerTexture(nullptr),
	m_playerSprite(nullptr),
	m_player(nullptr),
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

	// create texture memory
	m_playerTexture = new Texture();

	// create sprite memory 
	m_playerSprite = new Sprite();

	// create objects in memory
	m_player = new Player();

	// load textures
	m_playerTexture->LoadTexture(m_graphics, PLAYER_RESOURCE);

	// init sprites
	m_playerSprite->Init(m_playerTexture);

	// init game objects
	m_player->Init(m_playerSprite, Vector2((float)PLAYER_START_X, (float)PLAYER_START_Y));

	// set running to true
	m_running = true;
}

void GameplayGameState::DeleteAssets()
{
	// delete game objects
	if(m_player)
	{
		delete m_player;
		m_player = nullptr;
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
	// check if key is released
	///////////////////////////////////////////

	if(!m_input->IsKeyDown(PLAYER_UP_KEY))
	{
		// stop Y movement
		m_player->Stop(Controller::up);
	} else if(!m_input->IsKeyDown(PLAYER_DOWN_KEY))
	{
		// stop Y movement
		m_player->Stop(Controller::down);
	}

	if(!m_input->IsKeyDown(PLAYER_LEFT_KEY))
	{
		// stop X movement
		m_player->Stop(Controller::left);
	}else if(!m_input->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		// stop X movement
		m_player->Stop(Controller::right);
	}

	///////////////////////////////////////////
	// check if key is pressed down
	///////////////////////////////////////////

	if(m_input->IsKeyDown(PLAYER_UP_KEY))
	{
		// move player up
		m_player->Move(Controller::up);
	}
	else if(m_input->IsKeyDown(PLAYER_DOWN_KEY))
	{
		// move player down
		m_player->Move(Controller::down);
	}

	if(m_input->IsKeyDown(PLAYER_LEFT_KEY))
	{
		// move player left
		m_player->Move(Controller::left);
	}
	else if(m_input->IsKeyDown(PLAYER_RIGHT_KEY))
	{
		// move player right
		m_player->Move(Controller::right);
	}
}

void GameplayGameState::Update(float deltaTime)
{
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
