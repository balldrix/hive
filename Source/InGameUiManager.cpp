#include "InGameUiManager.h"
#include "Graphics.h"

InGameUiManager::InGameUiManager()
{
}

InGameUiManager::~InGameUiManager()
{
}

void InGameUiManager::Init(Graphics* graphics)
{
	m_despairFont12 = std::make_unique<SpriteFont>(graphics->GetDevice(), L"GameData//SpriteFonts//goodbye_despair_12pt.spritefont");
}

void InGameUiManager::Render(Graphics* graphics)
{
	m_despairFont12->DrawString(graphics->GetSpriteBatch(),
		L"99",
		Vector2(95, 2),
		Colors::YellowGreen, 0,
		Vector2::Zero
	);
}