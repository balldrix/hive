#include "ControlScreen.h"
#include "Constants.h"
#include "Colours.h"

ControlScreen::ControlScreen(GameStateManager* gm) :
m_pGM(gm),
m_pGraphics(NULL),
m_input(NULL),
GameState("CONTROLSCREEN")
{
	m_pGraphics = m_pGM->GetGraphics();
	m_input = m_pGM->GetInput();
}

ControlScreen::~ControlScreen()
{

}

void
ControlScreen::OnEntry()
{
	LoadAssets();
}

void
ControlScreen::OnExit()
{
	DeleteAssets();
}

void
ControlScreen::LoadAssets()
{

}

void
ControlScreen::DeleteAssets()
{
	
}

void
ControlScreen::CheckInput(float deltaTime)
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
	else if (!(m_input->IsKeyDown(PLAYER_UP_KEY) ||
		m_input->IsKeyDown(PLAYER_DOWN_KEY) ||
		m_input->IsKeyDown(PLAYER_LEFT_KEY) ||
		m_input->IsKeyDown(PLAYER_RIGHT_KEY) ||
		m_input->IsKeyDown(ENTER_KEY)
		))
	{
		m_keyPressed = false;
	}

	m_inputTimer += deltaTime;
}

void
ControlScreen::Update(float deltaTime)
{
	CheckInput(deltaTime);
}

void
ControlScreen::Render()
{

}
