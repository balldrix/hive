#include "FrontEnd.h"
#include "Constants.h"

FrontEnd::FrontEnd(GameStateManager* gm) :
m_pGM(gm),
m_pGraphics(NULL),
m_pInput(NULL),
GameState("FRONTEND")
{
	m_pGraphics = m_pGM->GetGraphics();
	m_pInput = m_pGM->GetInput();

	// loop through options and
	// NULL the sprite pointers
	

	// loop through option states
	// to initialise them to false
	
}

FrontEnd::~FrontEnd()
{
}

void
FrontEnd::OnEntry()
{
	LoadAssets();
}

void 
FrontEnd::OnExit()
{
	DeleteAssets();
}

void
FrontEnd::LoadAssets()
{
	// create and initialise new title sprite
	

	// initialise menu options
	
	// set menu state to 1 player as default
	
}

void
FrontEnd::DeleteAssets()
{
	
}

void
FrontEnd::CheckInput(float deltaTime)
{
	m_inputTimer = 0;

	if (!m_keyPressed)
	{
		m_keyPressed = true;
	}

	if (m_inputTimer > KEY_DELAY)
	{
		m_keyPressed = false;
	}
	else if (!(m_pInput->IsKeyDown(PLAYER_UP_KEY) ||
		m_pInput->IsKeyDown(PLAYER_DOWN_KEY) ||
		m_pInput->IsKeyDown(PLAYER_LEFT_KEY) ||
		m_pInput->IsKeyDown(PLAYER_RIGHT_KEY) ||
		m_pInput->IsKeyDown(ENTER_KEY)
		))
	{
		m_keyPressed = false;
	}

	m_inputTimer += deltaTime;
}

void
FrontEnd::Update(float deltaTime)
{
	CheckInput(deltaTime);
}

void
FrontEnd::Render()
{
	// Render game title logo thing
	

	// Render menu options
	
}

void
FrontEnd::SelectNext()
{
	// current selectState must be
	// flagged false before changing
	// to new menu state
	

	// check which is current state
	// and set new state in list
	

	// set new selectState as true
	// so the correct sprite frame is Rendern
	
}

void
FrontEnd::SelectPrevious()
{
	// current selectState must be
	// flagged false before changing
	// to new menu state
	

	// check which is current state
	// and set new state in list
	

	


	// set new selectState as true
	// so the correct sprite frame is drawn
	
}

void
FrontEnd::SetState(FrontEndMenuState state)
{
	// store menu state
	m_optionState = state;
}