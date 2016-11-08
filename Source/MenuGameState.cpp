#include "MenuGameState.h"
#include "GameStateManager.h"
#include "Graphics.h"
#include "Input.h"
#include "Audio.h"
#include "Texture.h"
#include "Sprite.h"
#include "Button.h"
#include "Instructions.h"
#include "Cursor.h"

MenuGameState::MenuGameState()
{
}

MenuGameState::MenuGameState(GameStateManager* gameStateManager) :
m_gameStateManager(nullptr),
m_graphics(nullptr),
m_input(nullptr),
m_audio(nullptr),
m_backgroundLoop(nullptr),
m_menuMusic(nullptr),
m_clickSound(nullptr),
m_backgroundTexture(nullptr),
m_playButtonTexture(nullptr),
m_instuctionsButtonTexture(nullptr),
m_quitButtonTexture(nullptr),
m_instructionsTexture(nullptr),
m_cursorTexture(nullptr),
m_backgroundSprite(nullptr),
m_playButtonSprite(nullptr),
m_instructionsButtonSprite(nullptr),
m_quitButtonSprite(nullptr),
m_instructionsSprite(nullptr),
m_cursorSprite(nullptr),
m_playButton(nullptr),
m_instructionsButton(nullptr),
m_quitButton(nullptr),
m_instructions(nullptr),
m_mouseCursor(nullptr),
GameState(L"MENU")
{
	// get essential pointers from gamestate manager
	m_gameStateManager = gameStateManager;
	m_graphics = m_gameStateManager->GetGraphics();
	m_input = m_gameStateManager->GetInput();
	m_audio = m_gameStateManager->GetAudio();
	
	m_input->SetMouseClicked(false); // set mouse clicked to false
}

MenuGameState::~MenuGameState()
{
}

void
MenuGameState::OnEntry()
{
	// load the assets for the menu state
	LoadAssets();
}

void 
MenuGameState::OnExit()
{
	// release memory and delete assets
	ReleaseAll();
	DeleteAssets();
}

void
MenuGameState::LoadAssets()
{	
	// load sounds
	m_clickSound = new SoundEffect(m_audio, L"Assets\\Sounds\\click.wav");
	m_menuMusic = new SoundEffect(m_audio, L"Assets\\Sounds\\menu.wav");
	
	// initialise background music
	m_backgroundLoop = m_menuMusic->CreateInstance();
	m_backgroundLoop->Play(true); // play in a loop
	m_backgroundLoop->SetVolume(0.5f); // reduce volume a little

	// create texture memory
	m_backgroundTexture = new Texture();
	m_playButtonTexture = new Texture();
	m_instuctionsButtonTexture = new Texture();
	m_quitButtonTexture = new Texture();
	m_instructionsTexture = new Texture();
	m_cursorTexture = new Texture();
	
	// create sprite memory
	m_backgroundSprite = new Sprite();
	m_playButtonSprite = new Sprite();
	m_instructionsButtonSprite = new Sprite();
	m_quitButtonSprite = new Sprite();
	m_instructionsSprite = new Sprite();
	m_cursorSprite = new Sprite();

	// create object memory
	m_playButton = new Button();
	m_instructionsButton = new Button();
	m_quitButton = new Button();
	m_instructions = new Instructions();
	m_mouseCursor = new Cursor();

	// load textures
	m_backgroundTexture->LoadTexture(m_graphics, "Assets//Textures//menuBackground.png");
	m_playButtonTexture->LoadTexture(m_graphics, "Assets//Textures//buttonPlay.png");
	m_instuctionsButtonTexture->LoadTexture(m_graphics, "Assets//Textures//ButtonInstructions.png");
	m_quitButtonTexture->LoadTexture(m_graphics, "Assets//Textures//buttonQuit.png");
	m_instructionsTexture->LoadTexture(m_graphics, "Assets//Textures//instructions.png");
	m_cursorTexture->LoadTexture(m_graphics, "Assets//Textures//cursor.png");

	// initalise sprites
	m_backgroundSprite->Init(m_backgroundTexture);
	m_playButtonSprite->Init(m_playButtonTexture);
	m_instructionsButtonSprite->Init(m_instuctionsButtonTexture);
	m_quitButtonSprite->Init(m_quitButtonTexture);
	m_instructionsSprite->Init(m_instructionsTexture);
	m_cursorSprite->Init(m_cursorTexture);
	m_cursorSprite->SetOrigin(Vector2(0.0f, 0.0f)); // set origin of sprite to top left for cursor acuracy

	// initalise play button
	m_playButton->Init(m_playButtonSprite, Vector2(m_graphics->GetWidth() * 0.225f, m_graphics->GetHeight() * 0.6f)); // init
	m_playButton->GetHitBox().OffSetAABB(m_playButton->GetPosition() - m_playButton->GetSprite()->GetOrigin()); // offset hitbox to correct position
	m_playButton->SetActive(true); // set active

	// initialise instructions button
	m_instructionsButton->Init(m_instructionsButtonSprite, Vector2(m_graphics->GetWidth() * 0.5f, m_graphics->GetHeight() * 0.6f)); // init
	m_instructionsButton->GetHitBox().OffSetAABB(m_instructionsButton->GetPosition() - m_instructionsButton->GetSprite()->GetOrigin()); // offset hitbox to correct position
	m_instructionsButton->SetActive(true); // set active

	// initialise quit button
	m_quitButton->Init(m_quitButtonSprite, Vector2(m_graphics->GetWidth() * 0.775f, m_graphics->GetHeight() * 0.6f)); // init
	m_quitButton->GetHitBox().OffSetAABB(m_quitButton->GetPosition() - m_quitButton->GetSprite()->GetOrigin()); // offset hitbox to correct position
	m_quitButton->SetActive(true); // set active
	
	// initialise instructions screen
	m_instructions->Init(m_instructionsSprite, Vector2(m_graphics->GetWidth() * 0.5f, m_graphics->GetHeight() * 0.55f)); // init
	m_instructions->SetActive(false); // set inactive to begin with

	// initialise cursor
	m_mouseCursor->Init(m_cursorSprite, Vector2((float)m_input->GetMouseX(), (float)m_input->GetMouseY())); // init
	m_mouseCursor->GetHitBox().SetAABB(Vector2(0.0f,0.0f), Vector2(0.0f,0.0f)); // cursor hitbox is only 1x1 pixel size
	m_mouseCursor->SetActive(true); // set active

	// ready for mouse click
	m_inputReady = true;
}

void
MenuGameState::DeleteAssets()
{	
	// delete mouse cursor
	if(m_mouseCursor)
	{
		delete m_mouseCursor;
		m_mouseCursor = nullptr;
	}

	// delete instructions screen
	if(m_instructions)
	{
		delete m_instructions;
		m_instructions = nullptr;
	}

	// delete quit button
	if(m_quitButton)
	{
		delete m_quitButton;
		m_quitButton = nullptr;
	}

	// delete instructions button
	if(m_instructionsButton)
	{
		delete m_instructionsButton;
		m_instructionsButton = nullptr;
	}

	// delete play game button
	if(m_playButton)
	{
		delete m_playButton;
		m_playButton = nullptr;
	}

	// delete mouse cursor sprite
	if(m_cursorSprite)
	{
		delete m_cursorSprite;
		m_cursorSprite = nullptr;
	}

	// delete instructions screen sprite
	if(m_instructionsSprite)
	{
		delete m_instructionsSprite;
		m_instructionsSprite = nullptr;
	}

	// delete quit button sprite
	if(m_quitButtonSprite)
	{
		delete m_quitButtonSprite;
		m_quitButtonSprite = nullptr;
	}

	// delete instructions button sprite
	if(m_instructionsButtonSprite)
	{
		delete m_instructionsButtonSprite;
		m_instructionsButtonSprite = nullptr;
	}

	// delete play button sprite
	if(m_playButtonSprite)
	{
		delete m_playButtonSprite;
		m_playButtonSprite = nullptr;
	}

	// delete background sprite
	if(m_backgroundSprite)
	{
		delete m_backgroundSprite;
		m_backgroundSprite = nullptr;
	}

	// delete mouse cursor texture
	if(m_cursorTexture)
	{
		delete m_cursorTexture;
		m_cursorTexture = nullptr;
	}

	// delete instructions screen texture
	if(m_instructionsTexture)
	{
		delete m_instructionsTexture;
		m_instructionsTexture = nullptr;
	}

	// delete quit button texture
	if(m_quitButtonTexture)
	{
		delete m_quitButtonTexture;
		m_quitButtonTexture = nullptr;
	}

	// delete instructions button texture
	if(m_instuctionsButtonTexture)
	{
		delete m_instuctionsButtonTexture;
		m_instuctionsButtonTexture = nullptr;
	}

	// delete play button texture
	if(m_playButtonTexture)
	{
		delete m_playButtonTexture;
		m_playButtonTexture = nullptr;
	}

	// delete background texture
	if(m_backgroundTexture)
	{
		delete m_backgroundTexture;
		m_backgroundTexture = nullptr;
	}

	// delete menu loop music
	if(m_menuMusic)
	{
		delete m_menuMusic;
		m_menuMusic = nullptr;
	}

	// delete button click sound
	if(m_clickSound)
	{
		delete m_clickSound;
		m_clickSound = nullptr;
	}
}

void
MenuGameState::ProcessInput()
{
	// quit when escape key is pressed
	if(m_input->IsKeyDown(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}

	// if mouse button is clicked
	if(m_input->GetMouseClicked())
	{
		m_mouseCursor->SetClicked(true); // set cursor to clicked
	}

	// toggle mouse click off when mouse button has been released
	if(!m_input->GetMouseClicked())
	{
		m_mouseCursor->SetClicked(false);
	}
}

void
MenuGameState::Update(float deltaTime)
{
	// update cursor
	m_mouseCursor->SetPosition(Vector2((float)m_input->GetMouseX(), (float)m_input->GetMouseY()));
	m_mouseCursor->Update(deltaTime);

	// if input status is ready
	if(m_inputReady)
	{
		// check if mouse was clicked this frame
		if(m_mouseCursor->IsClicked())
		{
			if(m_playButton->IsActive()) // check button is active
			{
				// check if mouse is over play button
				if(m_mouseCursor->GetHitBox().Collision(m_playButton->GetHitBox()))
				{
					// reset input toggle
					m_inputReady = false;

					// switch game state to gameplay state
					m_gameStateManager->SwitchState(L"GAMEPLAY");
					return;
				}
			}

			if(m_instructionsButton->IsActive()) // check button is active
			{
				// check if mouse is over instructions button
				if(m_mouseCursor->GetHitBox().Collision(m_instructionsButton->GetHitBox()))
				{
					// play sound
					m_clickSound->Play();

					//show instructions
					m_instructions->SetActive(true);

					// set buttons to inactive while instructions are shown
					m_playButton->SetActive(false);
					m_instructionsButton->SetActive(false);
					m_quitButton->SetActive(false);

					// reset input toggle
					m_inputReady = false;

					return;
				}
			}

			if(m_quitButton->IsActive()) // check button is active
			{
				// check if mouse is over quit button
				if(m_mouseCursor->GetHitBox().Collision(m_quitButton->GetHitBox()))
				{
					PostQuitMessage(0);
				}
			}

			// check if instructions are shown
			if(m_instructions->IsActive())
			{
				// play sound
				m_clickSound->Play();

				// set instructions to inactive
				m_instructions->SetActive(false);

				// set buttons to active
				m_playButton->SetActive(true);
				m_instructionsButton->SetActive(true);
				m_quitButton->SetActive(true);

				// reset input toggle
				m_inputReady = false;
				return;
			}
		}
	}

	// only deal with mouse click if 
	// mouse button has been released
	if(!m_mouseCursor->IsClicked())
	{
		m_inputReady = true; // input is ready
	}
}

void
MenuGameState::Render()
{
	// render background sprite first
	m_backgroundSprite->Render(m_graphics,
								Vector2(m_graphics->GetWidth() / 2, 
							   m_graphics->GetHeight() / 2));

	// render play button
	if(m_playButton->IsActive())
	{
		m_playButton->Render(m_graphics);
	}

	// render instruction button
	if(m_instructionsButton->IsActive())
	{
		m_instructionsButton->Render(m_graphics);
	}

	// render quit button
	if(m_quitButton->IsActive())
	{
		m_quitButton->Render(m_graphics);
	}

	// render instructions
	if(m_instructions->IsActive())
	{
		m_instructions->Render(m_graphics);
	}
	
	//////////////////////////////////////
	// render mouse cursor
	// always render last!
	if(m_mouseCursor->IsActive())
	{
		m_mouseCursor->Render(m_graphics);
	}
}

void
MenuGameState::ReleaseAll()
{
	// release all texture resources
	if(m_cursorTexture) { m_cursorTexture->Release(); }
	if(m_instructionsTexture) { m_instructionsTexture->Release(); }
	if(m_quitButtonTexture) { m_quitButtonTexture->Release(); }
	if(m_instuctionsButtonTexture) { m_instuctionsButtonTexture->Release(); }
	if(m_playButtonTexture)	{ m_playButtonTexture->Release(); }
	if(m_backgroundTexture) { m_backgroundTexture->Release(); }
	
	// release sounds
	m_backgroundLoop.reset();
}